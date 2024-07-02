/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:09:16 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/02 15:54:29 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exec(char *command, int status, char *check)
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
			return (126);
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

void	ft_free_all(t_cmds **ret, t_envp **lst, t_status *status, int flag)
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

int	check_redir_builtins(t_cmds *current, char list_builtins[][7])
{
	int	i;

	i = 0;
	if (current->code_id >= 11 && current->code_id <= 14)
	{
		if (!current->next && !current->next->next)
			return (-1);
		while (i < 7 && ft_strcmp(current->next->next->name, list_builtins[i]))
			i++;
		if (i != 7)
			return (i);
	}
	i = 0;
	if (!current->prev)
		return (-1);
	while (i < 7 && ft_strcmp(current->prev->name, list_builtins[i]))
		i++;
	if (i != 7)
		return (i);
	return (-1);
}

int	builtins_checker(t_cmds *current)
{
	char	list_builtins[7][7];
	int		i;

	if (!current || !current->name || !current->code_id)
		return (-1);
	ft_strlcpy(list_builtins[0], "echo", 5);
	ft_strlcpy(list_builtins[1], "cd", 3);
	ft_strlcpy(list_builtins[2], "pwd", 4);
	ft_strlcpy(list_builtins[3], "export", 7);
	ft_strlcpy(list_builtins[4], "unset", 6);
	ft_strlcpy(list_builtins[5], "env", 4);
	ft_strlcpy(list_builtins[6], "exit", 5);
	i = 0;
	while (i < 7 && ft_strcmp(current->name, list_builtins[i]))
		i++;
	if (i != 7)
		return (i);
	return (check_redir_builtins(current, list_builtins));
}