/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 21:10:30 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/17 12:14:20 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmds	*make_list(t_cmds *current)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->code_id = current->code_id;
	new->name = current->name;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
int	set_command(t_cmds **ret, t_cmds ***new_ret, int i, int num)
{
	t_cmds		*current_ret;
	t_cmds		*new;
	int			*pipe_posit;
	int			n;

	current_ret = *(ret);
	n = -1;
	pipe_posit = set_posit(ret, num);
	while (i != 0 && ++n < pipe_posit[i] + 1)
		current_ret = current_ret->next;
	*new_ret = malloc(sizeof(t_cmds));
	new = make_list(current_ret);
	if (!*new_ret || !new)
		return (-1);
	**new_ret = new;
	current_ret = current_ret->next;
	while (current_ret && current_ret->code_id != 10)
	{
		new->next = make_list(current_ret);
		new->next->prev = new;
		new = new->next;
		current_ret = current_ret->next;
	}
	free(pipe_posit);
	return (0);
}

void	free_fds(int **fds, int end)
{
	int	i;

	i = -1;
	while (i <= end)
		free(fds[i]);
	free(fds);
}

int	**malloc_fds(int num_pipes)
{
	int	**fds;
	int	i;

	fds = malloc(num_pipes * sizeof(int *));
	if (!fds)
		return (NULL);
	i = -1;
	while (++i < num_pipes)
	{
		fds[i] = malloc(2 * sizeof(int));
		if (pipe(fds[i]) == -1)
		{
			free_fds(fds, i);
			return (NULL);
		}
	}
	return (fds);
}

void	free_finish(int num_pipes, int *pids, int **fds)
{
	int	i;

	i = -1;
	while (++i <= num_pipes)
		waitpid(pids[i], NULL, 0);
	free(pids);
	i = -1;
	while (++i < num_pipes)
		free(fds[i]);
	free(fds);
}

int	execute_pipe(t_pipe *pipe, t_cmds **new_ret, int i)
{
	int	n;

	if (set_command(pipe->ret_save, &new_ret, i, pipe->num_pipes) == -1)
		return (-1);
	pipe->ret = new_ret;
	pipe->pids[i] = fork();
	if (pipe->pids[i] == 0)
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
		if (redirec_main(pipe))
			return (-1);
		exit(0);
	}
	return (0);
}

int	pipe_main2(t_cmds **ret, t_envp **list, t_file **file)
{
	t_pipe		pipe;
	t_cmds		**new_ret;
	int			i;

	new_ret = NULL;
	set_pipe(ret, list, file, &pipe);
	pipe.num_pipes = count_pipes(ret);
	if (!pipe.num_pipes)
		return (redirec_main(&pipe));
	pipe.fds = malloc_fds(pipe.num_pipes);
	pipe.pids = malloc((pipe.num_pipes + 1) * sizeof(int));
	if (!pipe.fds || !pipe.pids)
		return (-1);
	i = -1;
	while (++i <= pipe.num_pipes)
	{
		if (execute_pipe(&pipe, new_ret, i) == -1)
			return (-1);
	}
	i = -1;
	while (++i < pipe.num_pipes)
	{
		close(pipe.fds[i][0]);
		close(pipe.fds[i][1]);
	}
	free_finish(pipe.num_pipes, pipe.pids, pipe.fds);
	return (0);
}
