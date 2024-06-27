/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 21:10:30 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/27 12:55:01 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_fds(int **fds, int end)
{
	int	i;

	i = -1;
	while (i <= end)
		free(fds[i]);
	free(fds);
}

int	malloc_pipe(int num_pipes, t_pipe *p)
{
	int	i;

	p->fds = malloc(num_pipes * sizeof(int *));
	if (!p->fds)
		return (-1);
	i = -1;
	while (++i < num_pipes)
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
		free_fds(p->fds, num_pipes);
		return (-1);
	}
	return (0);
}

int	free_finish(int num_pipes, int *pids, int **fds)
{
	int	i;
	int status;

	i = -1;
	while (++i <= num_pipes)
		waitpid(pids[i], &status, 0);
	free(pids);
	i = -1;
	while (++i < num_pipes)
		free(fds[i]);
	free(fds);
	return (WEXITSTATUS(status));
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
		if (redirec_main(pipe, 1))
			exit(-1);
		exit(0);
	}
	return (0);
}

int	pipe_main(t_cmds **ret, t_envp **list, t_file **file)
{
	t_pipe		pipe;
	t_cmds		**new_ret;
	int			i;

	new_ret = NULL;
	set_pipe(ret, list, file, &pipe);
	pipe.num_pipes = count_pipes(ret);
	if (!pipe.num_pipes)
		return (redirec_main(&pipe, 0));
	if (malloc_pipe(pipe.num_pipes, &pipe) == -1)
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
	return (free_finish(pipe.num_pipes, pipe.pids, pipe.fds));
	return (0);
}
