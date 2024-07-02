/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:09:16 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/02 11:41:14 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_exec(char *command, int status, char *check)
{
	int	i;
	struct stat buff;

	if (status == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (stat(check, &buff) == 0 && !(buff.st_mode & S_IRUSR))
		{
			ft_putstr_fd(": Permission denied: ", 2);
			ft_putstr_fd(check, 2);
			ft_putstr_fd("\n", 2);
			return(126);
		}
		if (errno == ENOENT)
			ft_putstr_fd("No such file or directory: ", 2);
		else
			ft_putstr_fd("Command not found: ", 2);
		i = 4;
		while (command[++i])
			ft_putchar_fd(command[i], 2);
		ft_putstr_fd("\n", 2);
		return (127);
	}
	return (status);
}

void ft_free_all(t_cmds **ret, t_envp **lst, t_status *status, int flag)
{
	if (!flag)
	{
		free_envp(lst);
		free(lst);
		free_tcmd(ret);
	}
	else
	{
		free(status);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("parse error\n", 2);
		exit(139);
	}
}