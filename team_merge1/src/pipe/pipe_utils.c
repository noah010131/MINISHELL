/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:13:46 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 04:07:48 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(t_pars **commands)
{
	int		i;
	t_pars	*current;

	i = 0;
	current = (*commands);
	while (current->next)
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	check_heredoc(t_pars **commands)
{
	t_pars	*current;
	int		i;

	i = 0;
	current = *commands;
	while (current)
	{
		if (current->redirections && current->redirections->type == HEREDOC)
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}

int	check_place(t_pars **commands, int place)
{
	t_pars	*current;
	int		i;

	i = 0;
	current = *commands;
	while (current)
	{
		current = current->next;
		i++;
	}
	if (i == place)
		return (1);
	return (0);
}

void	pipe_operation(t_pipe *pipe, int i)
{
	int	n;

	if (i > 0)
		dup2(pipe->fds[i - 1][0], STDIN_FILENO);
	if (i < pipe->num_pipes)
	{
		if (!access(OUTPUT, F_OK))
		{
			pipe->fd = open(OUTPUT, O_RDWR | O_TRUNC, 0644);
			if (pipe->fd == -1)
				exit(-1);
			dup2(pipe->fd, STDIN_FILENO);
		}
		else
			dup2(pipe->fds[i][1], STDOUT_FILENO);
	}
	n = -1;
	while (++n < pipe->num_pipes)
	{
		if (pipe->fd != -1)
			close(pipe->fd);
		close(pipe->fds[n][0]);
		close(pipe->fds[n][1]);
	}
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
	p->fd = -1;
	return (0);
}
