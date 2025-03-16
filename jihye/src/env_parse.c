/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:50:40 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 20:27:46 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_equal(char *envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (ERR);
	while (envp[i])
	{
		if (envp[i] == '=')
			return (i);
		i++;
	}
	return (ERR);
}

bool	check_have_value(t_env *new_env, char *env_entry, int equal_pos)
{
	if (env_entry[equal_pos + 1] != '\0')
	{
		new_env->value = ft_strdup(env_entry + equal_pos + 1);
		if (!new_env->value)
		{
			ft_malloc_fail("check have value");
			return (false);
		}
	}
	else
		new_env->value = NULL;
	return (true);
}

t_env	*check_only_key(char *env_entry)
{
	t_env	*new_env;

	if (!env_entry)
		return (NULL);
	new_env = init_envp();
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(env_entry);
	new_env->origin_env = ft_strdup(env_entry);
	if (!new_env->key || !new_env->origin_env)
	{
		free_env(&new_env);
		ft_malloc_fail("check only key");
		return (NULL);
	}
	new_env->value = NULL;
	return (new_env);
}

t_env	*create_envp_node(char *env_entry)
{
	int		equal_pos;
	t_env	*new_env;

	equal_pos = find_equal(env_entry);
	if (equal_pos == ERR)
		return (check_only_key(env_entry));
	new_env = init_envp();
	if (!new_env)
		return (NULL);
	new_env->key = ft_strndup(env_entry, equal_pos);
	new_env->origin_env = ft_strdup(env_entry);
	if (!new_env->key || !new_env->origin_env)
	{
		free_env(&new_env);
		ft_malloc_fail("create envp node");
		return (NULL);
	}
	if (!check_have_value(new_env, env_entry, equal_pos))
	{
		free_env(&new_env);
		ft_malloc_fail("create envp node: value");
		return (NULL);
	}
	return (new_env);
}

void	env_parse(t_env_list **env_list, char **envp)
{
	int		i;
	t_env	*new_env;

	if (!env_list || !envp || !*envp)
	{
		ft_err_print_minishell("No env_list or envp");
		return ;
	}
	if (!(*env_list))
		init_env_list(env_list);
	i = 0;
	while (envp[i])
	{
		new_env = create_envp_node(envp[i]);
		if (!new_env)
			return ;
		*env_list = add_env_list_node(new_env, *env_list);
		i++;
	}
}
