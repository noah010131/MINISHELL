/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:13:30 by chanypar          #+#    #+#             */
/*   Updated: 2024/08/03 13:11:28 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exec_status(char *command, int status, char *check, int o_status)
{
	struct stat	buff;

	if (status == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (stat(check, &buff) == 0 && !(buff.st_mode & S_IRUSR))
		{
			ft_putstr_fd(": Permission denied\n", 2);
			ft_putstr_fd(check, 2);
			ft_putstr_fd("\n", 2);
			return (126);
		}
		if (errno == ENOENT)
			ft_putstr_fd("No such file or directory\n", 2);
		else
			ft_putstr_fd("Command not found\n", 2);
		return (127);
	}
	else if (o_status == 131)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (o_status);
	}
	return (status);
}

