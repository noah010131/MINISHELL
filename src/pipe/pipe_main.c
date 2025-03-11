/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:51:01 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/11 23:40:17 by chanypar         ###   ########.fr       */
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

	i = -1;
while (waitpid(-1, &status, 0) > 0) {
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
    }
	// while (++i <= num_pipes)
	// 	waitpid(pids[i], &status, 0);
	free(pids);
	i = -1;
	while (++i < num_pipes)
		free(fds[i]);
	free(fds);
	return (WEXITSTATUS(status));
	// return (0);
}

int	execute_pipe(t_pars *c, int i, t_pipe *pipe, t_envp **lst, t_ori *ori)
{
	int	n;

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
		if (redirec_main(c, lst, ori))
			exit(-1);
		exit(0);
	}
	return (0);
}

int	pipe_main(t_pars	**commands, t_envp **lst, t_ori *ori)
{
	t_pipe		pipe;
	t_pars		*save;
	int			i;
	int			checker;

	save = *commands;
	pipe.num_pipes = count_pipes(commands);
	if (!pipe.num_pipes)
		return (redirec_main(*commands, lst, ori));
	if (malloc_pipe(&pipe) == -1)
		return (-1);
	i = 0;
	checker = check_heredoc(commands);
	if (checker != -1)
	{
		while (i < checker)
		{
			(*commands) = (*commands)->next;
			i++;
		}
		read_heredoc((*commands)->redirections->filename, "wr", lst);
		if (checker == 0) //  first is heredoc
		{
			(*commands) = (*commands)->next;
			pipe.num_pipes -= 1;
		}
		else if (check_place(commands, checker))
			return (free_finish(pipe.num_pipes, pipe.pids, pipe.fds));
		else
		{
			while (checker > 1)
			{
				*commands = (*commands)->next;
				checker--;
			}
			pipe.num_pipes -= checker;
			(*commands)->redirections->type = 0;
		}
	}
	i = -1;
	while (*commands && ++i <= pipe.num_pipes)
	{
		if (execute_pipe(*commands, i, &pipe, lst, ori) == -1)
			return (-1);
		(*commands) = (*commands)->next;
	}
	i = -1;
	while (++i < pipe.num_pipes)
	{
		close(pipe.fds[i][0]);
		close(pipe.fds[i][1]);
	}
	*commands = save;
	return (free_finish(pipe.num_pipes, pipe.pids, pipe.fds));
}
