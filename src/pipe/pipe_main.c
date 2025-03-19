/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:51:01 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 04:07:48 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	execute_pipe(int i, t_pipe *pipe, t_ori *ori, t_pars *save)
{
	pipe->pids[i] = fork();
	if (pipe->pids[i] < 0)
		return (-1);
	else if (pipe->pids[i] == 0)
	{
		pipe_operation(pipe, i);
		if (save != (*ori->parsee) && pipe->num_pipes)
			free_pars(save, i);
		exit(redirec_main((*ori->parsee), ori->envs, ori, pipe));
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
	if (pipe->fd != -1)
		close(pipe->fd);
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
		if (execute_pipe(i, &pipe, ori, save) == -1)
			return (-1);
		*commands = (*commands)->next;
	}
	close_pipe(&pipe);
	*commands = save;
	return (free_finish(pipe.num_pipes, pipe.pids, pipe.fds));
}
