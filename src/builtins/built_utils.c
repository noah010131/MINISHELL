/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:21:39 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/17 22:19:10 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_hypen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	bad_id(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	if (!str)
		return (1);
	if (!(ft_isalpha(str[0]) || str[i] == '_'))
		return (1);
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
				&& str[i] != ' ') && check_hypen(str))
			return (1);
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (0);
}

int	update_env(t_envp **lst, char *key, char *n_value)
{
	t_envp	*current;

	if (!lst || !key)
		return (-1);
	current = *lst;
	while (current)
	{
		if (!ft_strcmp(key, current->name))
		{
			free(current->value);
			current->value = ft_strdup(n_value);
			return (0);
		}
		current = current->next;
	}
	return (0);
}
