/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_env_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:33:16 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 20:16:52 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*special_dollar_sign(char c, t_env_list *env_list)
{
	if (c == '?')
		return (env_list->flag = 42, ft_itoa(g_exit_code));
	return (ft_strdup(""));
}

char	*find_key(char *curr, int dollar, t_env_list *env_list)
{
	int		key_end;
	char	*key;

	key = NULL;
	if (curr[dollar + 1] == '$' || curr[dollar + 1] == '?')
		return (env_list->dollar_cnt = dollar + 2,
			special_dollar_sign(curr[dollar + 1], env_list));
	key_end = dollar + 1;
	while (curr[key_end] && (ft_isalnum(curr[key_end])
			|| curr[key_end] == '_'))
			key_end++;
	key = ft_strndup((curr + dollar + 1), (key_end - dollar - 1));
	if (!key)
		return (ft_malloc_fail("find key"), NULL);
	env_list->dollar_cnt = key_end;
	return (key);
}

char	*check_strcmp(t_env *curr)
{
	if (curr->value)
		return (ft_strdup(curr->value));
	else
		return (ft_strdup(""));
}

char	*compare_env_key(char *curr_str, int dollar, t_env_list *env_list)
{
	char	*key;
	char	*re;
	t_env	*curr;

	if (!env_list || !env_list->bottom)
		return (ft_err_print_minishell("compare env key: No environment value"),
			env_list->flag = ERR, NULL);
	re = NULL;
	key = find_key(curr_str, dollar, env_list);
	if (env_list->flag == 42)
		return (re = ft_strdup(key), free(key), re);
	if (!key)
		return (ft_strdup(""));
	curr = env_list->bottom;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (free(key), check_strcmp(curr));
		curr = curr->prev;
	}
	return (free(key), ft_strdup(""));
}
