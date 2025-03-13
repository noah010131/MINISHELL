/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:15:00 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/12 17:38:17 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_error_code(char *name)
{
	int	status;

	status = -1;
	ft_putstr_fd("minishell: ", 2);
	if (errno == ENOENT)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (errno == EACCES)
		ft_putstr_fd("Permission denied: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
	return (status);
}

int	close_file(t_redir *redirections)
{
	while (redirections)
	{
		if (redirections->f && !redirections->fd)
		{
			if (fclose(redirections->f) == -1)
				return (-1);
		}
		else if (redirections->fd != -1 && redirections->fd != 0)
		{
			if (close(redirections->fd) == -1)
				return (-1);
		}
		redirections = redirections->next;
	}
	if (access(TEMP, F_OK))
		unlink(TEMP);
	return (0);
}

int	reset_stdin_out(int copy_stdin_out[])
{
	if (copy_stdin_out[0])
	{
		if (dup2(copy_stdin_out[0], STDIN_FILENO) == -1)
		{
			copy_stdin_out[0] = 0;
			return (-1);
		}
	}
	if (copy_stdin_out[1])
	{
		if (dup2(copy_stdin_out[1], STDOUT_FILENO) == -1)
		{
			copy_stdin_out[1] = 0;
			return (-1);
		}
	}
	return (0);
}

int	ch_err(int num, int cpy_stdin_out[])
{
	if (num == -1)
	{
		reset_stdin_out(cpy_stdin_out);
		return (-1);
	}
	return (num);
}

void	free_redirections(t_redir *redirections)
{
	t_redir	*current;

	while (redirections)
	{
		current = redirections;
		redirections = redirections -> next;
		free(current);
	}
}
