/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:51:01 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/18 18:14:37 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	malloc_pipe(t_pipe *p)
{
	int	i;

	p->fds = malloc(p->num_pipes * sizeof(int *));
	if (!p->fds)
		return (-1);
	i = -1;
	while (++i < p->num_pipes)
	{
		p->fds[i] = malloc(2 * sizeof(int));
		if (pipe(p->fds[i]) == -1)
		{
			free_fds(p->fds, i);
			return (-1);
		}
	}
	p->pids = malloc((p->num_pipes + 1) * sizeof(int));
	if (!p->pids)
	{
		free_fds(p->fds, p->num_pipes);
		return (-1);
	}
	return (0);
}

int	free_finish(int num_pipes, int *pids, int **fds)
{
	int	i;
	int	status;
	int	exit_code;

	i = -1;
	while (++i <= num_pipes)
	{
		if (waitpid(pids[i], &status, 0) > 0)
			exit_code = WEXITSTATUS(status);
	}
	free(pids);
	i = -1;
	while (++i < num_pipes)
		free(fds[i]);
	free(fds);
	return (exit_code);
}

void	free_pars(t_pars *save, int i)
{
	t_pars	*current;
	t_pars	*tmp;
	t_redir	*current_r;
	t_redir	*tmp_r;

	if (!save)
		return ;
	current = save;
	while (i)
	{
		freee_error(current->arguments);
		tmp = current->next;
		current_r = current->redirections;
		while (current_r)
		{
			tmp_r = current_r->next;
			free(current_r->filename);
			free(current_r);
			current_r = tmp_r;
		}
		free(current);
		current = tmp;
		i--;
	}
	current = save;
}

int	execute_pipe(t_pars **c, int i, t_pipe *pipe, t_ori *ori, t_pars *save)
{
	int			n;

	(void)ori;
	(void)c;
	pipe->pids[i] = fork();
	if (pipe->pids[i] < 0)
		return (-1);
	else if (pipe->pids[i] == 0)
	{
		if (i > 0)
			dup2(pipe->fds[i - 1][0], STDIN_FILENO);
		if (i < pipe->num_pipes)
			dup2(pipe->fds[i][1], STDOUT_FILENO);
		n = -1;
		while (++n < pipe->num_pipes)
		{
			close(pipe->fds[n][0]);
			close(pipe->fds[n][1]);
		}
		if (save != *c && pipe->num_pipes)
			free_pars(save, i);
		exit(redirec_main(*c, ori->envs, ori, pipe));
	}
	return (0);
}

void	close_pipe(t_pipe	*pipe)
{
	int	i;

	i = -1;
	while (++i < pipe->num_pipes)
	{
		close(pipe->fds[i][0]);
		close(pipe->fds[i][1]);
	}
}

int	pipe_main(t_pars	**commands, t_envp **lst, t_ori *ori)
{
	t_pipe		pipe;
	t_pars		*save;
	int			i;

	i = 0;
	i = pipe_helper(commands, ori);
	if (i == -1 || i == -130)
		return (i * -1);
	pipe.num_pipes = count_pipes(commands);
	if (malloc_pipe(&pipe) == -1)
		return (-1);
	save = *commands;
	if (!pipe.num_pipes)
		return (redirec_main(*commands, lst, ori, &pipe));
	i = -1;
	while (++i <= pipe.num_pipes)
	{
		if (execute_pipe(commands, i, &pipe, ori, save) == -1)
			return (-1);
		*commands = (*commands)->next;
	}
	close_pipe(&pipe);
	*commands = save;
	return (free_finish(pipe.num_pipes, pipe.pids, pipe.fds));
}
