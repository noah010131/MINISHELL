/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:58:17 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/22 21:44:36 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// fonction qui a pour but de definir la taille de la
// valeur a expand

int	is_lim_exp(char c)
{
	if (c == ' ')
		return (1);
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

// fonction qui a pour but de trouver un equivalent de la valeur
// a expand dans le tableau d'environnement
// retourne null si erreur ou si il n y a
// pas de valeur correspondante
// retorune la value qui match si il y a un match
t_envp	*env_match(char *str, t_envp **lst)
{
	int		i;
	t_envp	*current;

	i = 0;
	if (!str || !str[0] || !lst)
		return (NULL);
	while (str[i] && is_lim_exp(str[i]) == 0)
		i++;
	current = *lst;
	while (current)
	{
		if (ft_strncmp(str, current->name, i) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	init_0(int *i, int *j)
{
	*i = 0;
	if (j)
		*j = 0;
}

int	interpret(char *str, char *ptr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i] && str + i != ptr)
	{
		if (str[i] == '"')
			flag = -flag;
		i++;
	}
	return (flag);
}
