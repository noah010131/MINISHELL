/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:09:16 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/17 17:07:18 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exec(char *command, int status, char *check, int o_status)
{
	int			i;
	struct stat	buff;

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
		ft_putstr_fd(command, 2);
		ft_putstr_fd("\n", 2);
		return (127);
	}
	else if (o_status == 131)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (o_status);
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

int	check_redir_builtins(t_cmds *c, char list_builtins[][7])
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (c->code_id >= 11 && c->code_id <= 14)
	{
		if (!c->next || !c->next->next)
			return (-1);
		while (i < 7 && ft_strcmp(c->next->next->name, list_builtins[i]))
			i++;
		if (i != 7)
			return (i);
		flag = 1;
	}
	i = 0;
	if (!c->prev && !flag)
		return (-1);
	while (c->prev && (i < 7 && ft_strcmp(c->prev->name, list_builtins[i])))
		i++;
	if (c->prev && i != 7)
		return (i);
	if (flag)
		return (-2);
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
