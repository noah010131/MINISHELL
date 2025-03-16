/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_env_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:33:16 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 19:53:07 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_only_dollar(char *curr, int dollar_after)
{
	while (curr[dollar_after] && curr[dollar_after] == '$')
		dollar_after++;
	if (curr[dollar_after] == '\0' || curr[dollar_after] == ' '
		|| curr[dollar_after] == '\t' || curr[dollar_after] == '\n')
	{
		ft_err_print_minishell("find key: only dollar");
		return (true);
	}
	return (false);
}

char	*find_key(char *curr, int dollar)
{
	int		key_end;
	char	*key;

	key_end = dollar + 1;
	if (curr[0] == '$' && curr[1] == '\0')
		return (ft_strdup("$"));
	if (!check_only_dollar(curr, key_end))
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

	curr = env_list->bottom;
	if (!curr)
	{
		ft_err_print_minishell("compare env key: No environment value");
		return (NULL);
	}
	key = find_key(curr_str, dollar);
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
