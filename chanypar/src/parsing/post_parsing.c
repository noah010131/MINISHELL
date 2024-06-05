/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:39:20 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/25 18:21:44 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmds	**pptreatment(t_cmds **cmds)
{
	t_cmds	*current;

	if (!cmds)
		return (NULL);
	current = *cmds;
	while (current)
	{
		replace_quote(current);
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
		if (!str[i])
			return (str[j] = 0, 0);
		str[j++] = str[i++];
	}
	str[j] = 0;
	return (0);
}
