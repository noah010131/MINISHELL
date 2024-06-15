/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:39:55 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/15 17:56:45 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtins_checker(t_cmds *current)
{
	char	list_butilins[7][7];
	int		i;

	if (!current || !current->name)
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