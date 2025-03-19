/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:51:26 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 15:00:02 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ERR);
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
	suffix = get_suffix(curr, env_list->dollar_cnt);
	merge = ft_strjoin(tmp, env_value);
	if (!tmp && env_value)
		merge = env_value;
	free(tmp);
	free(env_value);
	if (!merge)
		return (suffix);
	if (suffix)
	{
		tmp = merge;
		merge = ft_strjoin(tmp, suffix);
		if (tmp)
			free(tmp);
		free(suffix);
		return (merge);
	}
	return (merge);
}

void	process_token(t_token *curr, t_env_list *env_list)
{
	int		dollar;
	char	*new_str;

	dollar = find_dollar(curr->str);
	while (curr->str && dollar != ERR
		&& dollar < (int)ft_strlen(curr->str))
	{
		new_str = env_value_merge(curr->str, dollar, env_list);
		free(curr->str);
		curr->str = new_str;
		//printf("curr->str = [%s]\n", curr->str);
		//printf("str : [%s]\n", curr->str);
		dollar = find_dollar(curr->str);
	}
}

void	expand_env(t_token_list *token_list, t_env_list *env_list)
{
	t_token	*curr;

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
