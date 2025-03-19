/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:42:25 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 11:11:21 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		free(current->origin_env);
		free(current);
		current = tmp;
	}
	*lst = NULL;
	return (NULL);
}

t_envp	**add_envplast2(t_envp **ret, t_env *origin)
{
	t_envp	*current;
	t_envp	*new;

	if (!ret || !origin)
		return (NULL);
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->name = ft_strdup(origin->key);
	new->value = ft_strdup(origin->value);
	new->origin_env = ft_strdup(origin->origin_env);
	new->next = NULL;
	new->prev = NULL;
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

t_envp	**lst_env(t_env *bottom)
{
	t_env	*tmp;
	t_envp	**head;

	tmp = bottom;
	if (!bottom)
		return (NULL);
	head = malloc(sizeof(t_envp *));
	if (!head)
		return (NULL);
	*head = NULL;
	while (tmp)
	{
		head = add_envplast2(head, tmp);
		if (!head)
			return (free_envp(head));
		tmp = tmp->prev;
	}
	return (head);
}

t_env	*create_envp_node2(t_envp *origin)
{
	t_env	*new_env;

	new_env = init_envp();
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(origin->name);
	new_env->value = ft_strdup(origin->value);
	new_env->origin_env = ft_strdup(origin->origin_env);
	return (new_env);
}

void	transfer_env(t_data *data, t_ori *ori, char **envp)
{
	ori->envs = lst_env(data->env_list->bottom);
	ori->env = envp;
}

void	synchro_env(t_data *data, t_ori *ori)
{
	t_envp	*head;
	t_env	*new_env;

	head = *ori->envs;
	free_env_list(&data->env_list);
	init_env_list(&data->env_list);
	while (head)
	{
		new_env = create_envp_node2(head);
		if (!new_env)
			return ;
		data->env_list = add_env_list_node(new_env, data->env_list);
		head = head->next;
	}
}
