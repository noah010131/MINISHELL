/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:51:26 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 21:36:34 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_suffix(char *curr, int dollar)
{
	int		key_end;
	char	*suffix;

	key_end = dollar + 1;
	while (curr[key_end] && curr[key_end] != ' '
		&& curr[key_end] != '\t' && curr[key_end] != '\n')
		key_end++;
	suffix = ft_strdup(curr + key_end);
	if (!suffix)
	{
		ft_malloc_fail("get suffix");
		return (NULL);
	}
	return (suffix);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		ft_err_print_minishell("find dollar: No str");
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (ERR);
}

char	*env_value_merge(char *curr, int dollar, t_env_list *env_list)
{
	char	*tmp;
	char	*env_value;
	char	*suffix;
	char	*merge;

	tmp = ft_substr(curr, 0, dollar);
	env_value = compare_env_key(curr, dollar, env_list);
	suffix = get_suffix(curr, dollar);
	merge = ft_strjoin(tmp, env_value);
	free(tmp);
	tmp = merge;
	merge = ft_strjoin(tmp, suffix);
	free(tmp);
	free(env_value);
	free(suffix);
	return (merge);
}

void	expand_env(t_token_list *token_list, t_env_list *env_list)
{
	int		dollar;
	char	*new_str;
	t_token	*curr;

	if (!token_list || !env_list)
		ft_err_print_minishell("No tokens or env");
	curr = token_list->bottom;
	while (curr)
	{
		if (curr->str && (curr->type == DQ || curr->type == W))
		{
			dollar = find_dollar(curr->str);
			while (curr->str && dollar != ERR
				&& dollar < (int)ft_strlen(curr->str))
			{
				new_str = env_value_merge(curr->str, dollar, env_list);
				free(curr->str);
				curr->str = new_str;
				dollar = find_dollar(curr->str);
			}
		}
		curr = curr->prev;
	}
}
