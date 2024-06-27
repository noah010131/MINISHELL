/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:19:16 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/26 22:15:54 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
fonction qui va nous aider a recuper le tableau d environnement et le rendre
maleable afin de pouvoir travailler
dessus et l actualiser au fil des commandes

*/

t_envp	**lst_env(char **env)
{
	t_envp	**head;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	head = malloc(sizeof(t_envp *));
	if (!head)
		return (NULL);
	*head = NULL;
	while (env[i])
	{
		head = add_envplast(head, env[i]);
		if (!head)
			return (free_envp(head));
		i++;
	}
	return (head);
}

int	ft_tablen(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i])
		i++;
	return (i);
}

t_envp	**add_envplast(t_envp **ret, char *str)
{
	t_envp	*current;
	t_envp	*new;

	if (!ret || !str)
		return (NULL);
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->name = ft_strlimdup(str, ft_pos_c(str, '='));
	new->value = ft_strdup(str + ft_pos_c(str, '=') + 1);
	new->next = NULL;
	new->prev = NULL;
	new->unset = 0;
	if (!*ret)
	{
		*ret = new;
		return (ret);
	}
	current = *ret;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (ret);
}

void	*free_envp(t_envp **lst)
{
	t_envp	*current;
	t_envp	*tmp;

	if (!lst)
		return (NULL);
	if (!(*lst))
		return (free(lst), NULL);
	current = *lst;
	while (current)
	{
		tmp = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = tmp;
	}
	*lst = NULL;
	return (NULL);
}
