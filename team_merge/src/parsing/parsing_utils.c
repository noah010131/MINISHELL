/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:33:59 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/18 01:34:50 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envp	*env_match(char *str, t_envp **lst)
{
	int		i;
	t_envp	*current;

	i = 0;
	if (!str || !str[0] || !lst || !*lst)
		return (NULL);
	if (str[i] == '?')
		return (NULL);
	while (str[i] && is_lim_exp(str[i]) == 0)
		i++;
	current = *lst;
	while (current)
	{
		if (ft_stricmp(str, current->name, i) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	expanding(t_cmds **cmds, t_envp **lst)
{
	t_cmds	*current;
	int		flag;

	flag = 0;
	if (!cmds || !lst || !*cmds)
		return (-1);
	while (flag == 0)
	{
		flag = 1;
		current = *cmds;
		while (current)
		{
			if (nb_expand(current) > 0)
			{
				flag = 0;
				replace_exp(current, lst);
				if (!current->name)
					return (-1);
			}
			current = current->next;
		}
	}
	return (1);
}

int	exp_exception(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && (!is_lim_exp(str[i + 1]) || str[i + 1] == '?'))
			count++;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (!str[i])
				return (count);
		}
		i++;
	}
	return (count);
}