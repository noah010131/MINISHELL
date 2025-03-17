/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:13:30 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 22:11:58 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

void	print_no_command(char *argument)
{
	(void)argument;
	print_error("minishell: : command not found\n");
}

int	check_direc(char *cmd)
{
	struct stat	statbuf;

	if (lstat(cmd, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	print_message(char *argument, int num)
{
	char	*str;

	str = NULL;
	if (num == 1)
		str = ft_strjoin(argument, ": Is a directory\n");
	else if (num == 2)
		str = ft_strjoin(argument, ": No such file or directory\n");
	else if (num == 3)
		str = ft_strjoin(argument, ": Permission denied\n");
	else if (num == 4)
		str = ft_strjoin(argument, ": command not found\n");
	if (!str)
		return ;
	print_error(str);
	free(str);
}

int	check_error(char *command, char **arguments, int status)
{
	struct stat sb;

	if (!status)
		return (status);
	if (command)
		stat(command, &sb);
	if (ft_strchr(arguments[0], '/'))
	{
		if (check_direc(arguments[0]))
			(print_message(arguments[0], 1), status = 126);
		else if (access(arguments[0], F_OK) == -1)
			(print_message(arguments[0], 2), status = 127);
		else if (access(arguments[0], X_OK | R_OK) == -1)
			(print_message(arguments[0], 3), status = 126);
	}
	else
	{
		if (!command || S_ISDIR(sb.st_mode) || !(sb.st_mode & S_IXUSR))
			(print_message(arguments[0], 4), status = 127);
		else if (ft_strcmp(command, "NULL") == 0)
			(print_message(arguments[0], 2), status = 127);
		else if (access(command, X_OK) == -1)
			(print_message(arguments[0], 3), status = 126);
	}
	return (status);
}
