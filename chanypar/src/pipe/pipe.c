/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:55:58 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/07 15:55:37 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	duplicator2(int *fd[], int i, int num)
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

int	fork_pid(int *i, int *fd[], int *cmds_posit, t_cmds **ret)
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
		execute_command();
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
			current->next;
	}
	return (i);
}

int	pipe_main(t_cmds **ret, t_envp **list, t_file **file)
{
	int		*cmds_posit;
	int		i[2];
	int		num;
	int		fd[2][2];

	i[0] = -1;
	i[1] = count_pipes(ret);
	cmds_posit == set_posit(ret, i[1]);
	if (i[1] == 0)
		return (-1);
	while (++i[0] < i[1])
	{
		if (i[0] > 0)
		{
			fd[0][0] = fd[1][0];
			fd[0][1] = fd[1][1];
		}
		fork_pid(i[0], fd, cmds_posit, ret);
	}
	free(cmds_posit);
	return (0);
}
