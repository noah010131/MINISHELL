/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:55:58 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/13 16:29:15 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	duplicator2(int (*fd)[2], int i, int num)
{
	if (i > 0)
	{
		dup2(fd[0][1], STDIN_FILENO);
		close(fd[0][0]);
		close(fd[0][1]);
	}
	if (i < num - 1)
	{
		close(fd[1][0]);
		dup2(fd[1][1], STDOUT_FILENO);
		close(fd[1][1]);
	}
}

int	excute_cmds(int i, int *cmds_posit, t_pipe *pip)
{
	int		n;
	int		cmds;
	int		res_v;

	n = -1;
	while (++n < cmds_posit[i])
		pip->current = pip->current->next;
	res_v = redirec_main(pip);
	if (res_v == 1)
	{
		cmds = builtins_checker(pip->current);
		parsing_command(cmds, pip->current, pip->lst, pip->ret);
	}
	else if (res_v == -1)
	{
		pip->current = *(pip->ret);
		return (-1);
	}
	pip->current = *(pip->ret);
	return (0);
}

int	fork_pid(int *i, int (*fd)[2], int *cmds_posit, t_pipe *pip)
{
	int	pid;

	if (i[0] < i[1] - 1)
	{
		if (pipe(fd[1]) == -1 )
			return (-1);
	}
	pid = -1;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		duplicator2(fd, i[0], i[1]);
		if (excute_cmds(i[0], cmds_posit, pip) == -1)
			return (-1);
	}
	else if (i[0] > 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
	}
	return (0);
}

int	count_pipes(t_cmds **ret)
{
	int		i;
	t_cmds	*current;

	i = 0;
	current = *(ret);
	while (current->next)
	{
		current = find_name(current, 'p');
		if (!current)
			return (i);
		if (current->next)
		{
			current = current->next;
			i++;
		}
	}
	return (i);
}

int	pipe_main(t_cmds **ret, t_envp **list, t_file **file)
{
	t_pipe	pipe;
	int		*cmds_posit;
	int		i[2];
	int		fd[2][2];

	i[0] = -1;
	i[1] = count_pipes(ret);
	cmds_posit = set_posit(ret, i[1]);
	set_pipe(ret, list, file, &pipe);
	if (i[1] == 0)
		return (redirec_main(&pipe));
	while (++i[0] < i[1])
	{
		if (i[0] > 0)
		{
			fd[0][0] = fd[1][0];
			fd[0][1] = fd[1][1];
		}
		fork_pid(i, fd, cmds_posit, &pipe);
	}
	free(cmds_posit);
	return (0);
}
