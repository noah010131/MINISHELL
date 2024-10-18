/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:13:30 by chanypar          #+#    #+#             */
/*   Updated: 2024/10/18 11:09:21 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	check_exec_status(char *command, int status, char *check, int o_status)
// {
// 	struct stat	buff;

// 	(void)command;
// 	if (status == 1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		if (stat(check, &buff) == 0 && !(buff.st_mode & S_IRUSR))
// 			(ft_putstr_fd(": Permission denied\n", 2), status = 126);
// 		else if (errno == ENOENT)
// 			ft_putstr_fd("No such file or directory\n", 2);
// 		else
// 			ft_putstr_fd("Command not found\n", 2), status = 127;
// 	}
// 	else if (o_status == 131)
// 		(ft_putstr_fd("Quit (core dumped)\n", 2) , status = o_status);
// 	return (status);
// }

int	check_direc(char *cmd)
{
	struct stat	statbuf;

	if (lstat(cmd, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	check_error(char *command, char **arguments, int status)
{
	if (!status)
		return (status);
	ft_putstr_fd(arguments[0], 2);
	if (ft_strchr(arguments[0], '/'))
	{
		if (check_direc(arguments[0]))
			(ft_putendl_fd(": Is a directory", 2), status = 126);
		else if (access(arguments[0], F_OK) == -1)
			(ft_putendl_fd(": No such file or directory", 2), status = 127);
		else if (access(arguments[0], X_OK | R_OK) == -1)
			(ft_putendl_fd(": Permission denied", 2), status = 126);
	}
	else
	{
		if (!command)
			(ft_putendl_fd(": command not found", 2), status = 127);
		else if (ft_strcmp(command, "NULL") == 0)
			(ft_putendl_fd(": No such file or directory", 2), status = 127);
		else if (access(command, X_OK) == -1)
			(ft_putendl_fd(": Permission denied", 2), status = 126);
	}
	return (status);
}