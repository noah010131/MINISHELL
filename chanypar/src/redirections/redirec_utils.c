/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:25:44 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/07 14:20:14 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmds	*find_name(t_cmds *current, char name)
{
	t_cmds	*null;

	if (name == 'r')
	{
		while (current->next
			&& (current->code_id >= 11 && current->code_id <= 14))
			current = current->next;
	}
	else
	{
		while (current->next && current->code_id == 10)
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

int	builtins_checker(t_cmds *current)
{
	char	list_butilins[7][7];
	int		i;

	if (!current->prev)
		retrun (-1);
	ft_strlcpy(list_butilins[0], "echo", 5);
	ft_strlcpy(list_butilins[1], "cd", 3);
	ft_strlcpy(list_butilins[2], "pwd", 4);
	ft_strlcpy(list_butilins[3], "export", 7);
	ft_strlcpy(list_butilins[4], "unset", 6);
	ft_strlcpy(list_butilins[5], "env", 4);
	ft_strlcpy(list_butilins[6], "exit", 5);
	i = 0;
	while (ft_strcmp(current->prev->name, list_butilins[i]))
		i++;
	if (!(ft_strcmp(current->prev->name, list_butilins[i])))
		return (i);
	i = 0;
	if (!current->prev->prev)
		return (-1);
	while (ft_strcmp(current->prev->prev->name, list_butilins[i]))
		i++;
	if (!(ft_strcmp(current->prev->prev->name, list_butilins[i])))
		return (i);
	return (-1);
}

void	execute_command(int i, t_cmds *cmds, t_envp **lst)
{
	if (i == 0)
		ft_echo(cmds);
	if (i == 1)
		ft_cd(cmds, lst);
	if (i == 2)
		// pwd
	if (i == 3)
		// export
	if (i == 4)
		// unset
	if (i == 5)
		// env
	if (i == 6)
		// exit
}
