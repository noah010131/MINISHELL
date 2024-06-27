/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:39:20 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/27 14:41:03 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	freeonetcmd(t_cmds *cmd)
{
	if (!cmd)
		return ;
	if (cmd->prev)
		cmd->prev->next = cmd->next;
	if (cmd->next)
		cmd->next->prev = cmd->prev;
	if (cmd->name)
		free(cmd->name);
	free(cmd);
}

t_cmds	**pptreatment(t_cmds **cmds)
{
	t_cmds	*current;
	char	*str;

	if (!cmds)
		return (NULL);
	current = *cmds;
	while (current)
	{
		replace_quote(current);
		str = current->name;
		if (str[0] == 0)
			freeonetcmd(current);
		current = current->next;
	}
	return (cmds);
}

int	replace_quote(t_cmds *cmds)
{
	int		i;
	int		j;
	char	c;
	char	*str;

	i = 0;
	j = 0;
	if (!cmds || !cmds->name)
		return (0);
	str = cmds->name;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				str[j++] = str[i++];
			i++;
		}
		else
			str[j++] = str[i++];
		if (!str[i])
			return (str[j] = 0, 0);
	}
	str[j] = 0;
	return (0);
}
