/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:39:55 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/16 20:25:27 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_cmds	*check_posit(t_cmds *current)
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
		if (i == -2)
			c = c->next->next;
		return (exec_command(c, ret));
	}
	return (0);
}
