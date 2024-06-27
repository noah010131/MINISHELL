/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:39:55 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/27 15:33:29 by chanypar         ###   ########.fr       */
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
	t_cmds	*null;

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
	{
		null = malloc(sizeof(t_cmds));
		null->code_id = 0;
		null->name = NULL;
		null->next = NULL;
		null->prev = NULL;
		return (null);
	}
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

int check_exec(char *command, int status)
{
	int	i;

	if (status == 1)
	{
		ft_putstr_fd("minishell: ", 2);
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

int	parsing_command(int i, t_cmds *c, t_envp **lst, t_cmds **ret)
{
	if (c->prev && c->code_id != 9)
		c = c->prev;
	if (c->prev && ft_strcmp(c->name, "cd") && ft_strcmp(c->name, "echo"))
		c = c->prev;
	if (i == 0)
		return (ft_echo(c, ret));
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
		if (!c->code_id)
			return (0);
		return (exec_command(c, ret));
	}
	return (0);
}


