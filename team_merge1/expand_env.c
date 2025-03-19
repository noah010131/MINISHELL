/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:14:13 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 02:29:22 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*env_value_merge(char *curr, int dollar, t_env_list *env_list)
{
	int key_end;
	char *tmp;
	char *key;
	char	*merge;

	tmp = ft_substr(curr, 0, dollar);
	while (curr[dollar] == '$' && curr[dollar + 1] == '$')
		dollar++;
	key_end = dollar;
	if (key_end % 2 == 0)
		merge = ft_strjoin(tmp, ft_strdup(curr + key_end));
	else
	{
		key_end += 1;
		while (curr[key_end] && (ft_isalnum(curr[key_end])
				|| curr[key_end] == '_'))
			key_end++;
		key = ft_strndup((curr + dollar), (key_end - dollar - 1));
		if (!key)
			return (ft_malloc_fail("find key"), NULL);
		key = compare_env_key2(key, env_list);
	}
}

void process_token(t_token * curr, t_env_list * env_list)
{		
	int dollar;
	char *new_str;

	dollar = find_dollar(curr->str);
	while (curr->str && dollar != ERR && dollar < (int)ft_strlen(curr->str))
	{
		new_str = env_value_merge(curr->str, dollar, env_list);
		free(curr->str);
		curr->str = new_str;
		// printf("str : [%s]\n", curr->str);
		dollar = find_dollar(curr->str);
	}
}

void expand_env(t_token_list * token_list, t_env_list * env_list)
{
	t_token *curr;

	if (!token_list || !env_list)
	{
		ft_err_print_minishell("No tokens or env");
		return ;
	}
	curr = token_list->bottom;
	while (curr)
	{
		if (curr->str && (curr->type == DQ || curr->type == W))
			process_token(curr, env_list);
		curr = curr->prev;
	}
}