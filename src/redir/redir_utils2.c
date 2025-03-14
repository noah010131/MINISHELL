/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:15:00 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/14 10:59:57 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_error_code(char *name)
{
	char	*str;
	char	*str2;

	str = NULL;
	str2 = NULL;
	str = ft_strjoin("minishell: ", name);
	if (!str)
		return ;
	if (errno == ENOENT)
		str2 = ft_strjoin(str, ": no such file or directory\n");
	else if (errno == EACCES)
		str2 = ft_strjoin(str, ": Permission denied\n");
	else if (errno == EISDIR)
		str2 = ft_strjoin(str, ": Is a directory\n");
	else
		str2 = ft_strjoin(str, ": ambiguous redirect\n");
	if (!str2)
		return ;
	print_error(str2);
	free(str2);
	free(str);
}
// if error do not close file in error
int	close_file(t_redir *redirections)
{
	while (redirections)
	{
		if (redirections->f && redirections->fd)
		{
			if (fclose(redirections->f) == -1)
				return (-1);
		}
		else if (redirections->fd != -1 && redirections->fd != 0 )
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
	if (copy_stdin_out[0] > 0)
	{
		if (dup2(copy_stdin_out[0], STDIN_FILENO) == -1)
		{
			copy_stdin_out[0] = 0;
			return (-1);
		}
	}
	if (copy_stdin_out[1] > 0)
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
	if (num == -1 || num == 130)
	{
		if (num == 130)
			num *= -1;
		reset_stdin_out(cpy_stdin_out);
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
