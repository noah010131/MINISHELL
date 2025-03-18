/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_env_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:33:16 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/17 15:49:20 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_only_dollar(char *curr, int dollar)
{
	if (curr[dollar] == '\0' || curr[dollar] == ' '
		|| curr[dollar] == '\t' || curr[dollar] == '\n'
		|| curr[dollar] == '$')
		return (ERR);
	return (dollar);
}

char	*find_key(char *curr, int dollar)
{
	int		key_end;
	char	*key;

	key_end = dollar + 1;
	key = NULL;
	if (curr[0] == '$' && curr[1] == '\0')
		return (ft_strdup("$"));
	key_end = check_only_dollar(curr, key_end);
	if (key_end != ERR)
	{
		while (curr[key_end] && (ft_isalnum(curr[key_end])
				|| curr[key_end] == '_'))
			key_end++;
		key = ft_strndup((curr + dollar + 1), (key_end - dollar - 1));
		if (!key)
		{
			ft_malloc_fail("find key");
			return (NULL);
		}
	}
	return (key);
}

char	*compare_env_key(char *curr_str, int dollar, t_env_list *env_list)
{
	char	*key;
	t_env	*curr;

	if (!env_list || !env_list->bottom)
	{
		ft_err_print_minishell("compare env key: No environment value");
		env_list->flag = ERR;
		return (NULL);
	}
	key = find_key(curr_str, dollar);
	if (!key)
		return (ft_strdup(""));
	curr = env_list->bottom;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (curr->value)
				return (free(key), ft_strdup(curr->value));
			else
				return (free(key), ft_strdup(""));
		}
		curr = curr->prev;
	}
	return (free(key), ft_strdup(""));
}
