/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:21:39 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/16 20:26:58 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
