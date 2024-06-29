/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:39:55 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/29 15:13:52 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtins_checker(t_cmds *current)
{
	char	list_butilins[7][7];
	int		i;

	if (!current || !current->name || !current->code_id)
		return (-1);
	ft_strlcpy(list_butilins[0], "echo", 5);
	ft_strlcpy(list_butilins[1], "cd", 3);
	ft_strlcpy(list_butilins[2], "pwd", 4);
	ft_strlcpy(list_butilins[3], "export", 7);
	ft_strlcpy(list_butilins[4], "unset", 6);
	ft_strlcpy(list_butilins[5], "env", 4);
	ft_strlcpy(list_butilins[6], "exit", 5);
	i = 0;
	while (i < 7 && ft_strcmp(current->name, list_butilins[i]))
		i++;
	if (i != 7)
		return (i);
	i = 0;
	if (current->code_id >= 11 && current->code_id <= 14)
	{
		if (!current->next && !current->next->next)
			return (-1);
		while (i < 7 && ft_strcmp(current->next->next->name, list_butilins[i]))
			i++;
		if (i != 7)
			return (i);
	}
	i = 0;
	if (!current->prev)
		return (-1);
	while (i < 7 && ft_strcmp(current->prev->name, list_butilins[i]))
		i++;
	if (i != 7)
		return (i);
	return (-1);
}

t_cmds	*find_name(t_cmds *current, char name)
{
	if (name == 'r')
	{
		while (current->next && (current->code_id != 10)
			&& (!(current->code_id >= 11 && current->code_id <= 14)))
			current = current->next;
	}
	else
	{
		while (current->next && current->code_id != 10)
			current = current->next;
	}
	if (!current->next)
		return (NULL);
	return (current);
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

t_cmds *check_posit(t_cmds *current)
{
	if (current->code_id >= 11 && current->code_id <= 14)
	{
		if (current->next)
			current = current->next->next;
	}
	return (current);
}

int	parsing_command(int i, t_cmds *c, t_envp **lst, t_cmds **ret)
{
	if (c->prev && c->code_id != 9)
		c = c->prev;
	if (c->prev && ft_strcmp(c->name, "cd") && ft_strcmp(c->name, "echo"))
		c = c->prev;
	if (i == 0)
		return (ft_echo(check_posit(c), ret));
	else if (i == 1)
		return (ft_cd(c, lst));
	else if (i == 2)
		return (ft_pwd(c, lst));
	else if (i == 3)
		return (ft_export(c, lst));
	else if (i == 4)
		return (ft_unset(lst, c));
	else if (i == 5)
		return (ft_env(lst));
	else if (i == 6)
		return (ft_exit(ret));
	else
	{
		if (c->code_id == 0 || (c->code_id >= 11 && c->code_id <= 14))
			return (0);
		return (exec_command(c, ret));
	}
	return (0);
}


