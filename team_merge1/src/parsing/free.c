/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:51:40 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/17 14:34:57 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(t_token **token)
{
	if (!token || !*token)
		return ;
	if ((*token)->str)
	{
		free((*token)->str);
		(*token)->str = NULL;
	}
	free(*token);
	(*token) = NULL;
}

void	free_token_list(t_token_list **token_list)
{
	t_token	*curr;
	t_token	*prev;

	if (!token_list || !*token_list)
		return ;
	curr = (*token_list)->bottom;
	while (curr)
	{
		prev = curr->prev;
		free_token(&curr);
		curr = prev;
	}
	free(*token_list);
	*token_list = NULL;
}

void	free_env(t_env **env)
{
	if (!env || !*env)
		return ;
	if ((*env)->key)
	{
		free((*env)->key);
		(*env)->key = NULL;
	}
	if ((*env)->value)
	{
		free((*env)->value);
		(*env)->value = NULL;
	}
	if ((*env)->origin_env)
	{
		free((*env)->origin_env);
		(*env)->origin_env = NULL;
	}
	free(*env);
	(*env) = NULL;
}

void	free_env_list(t_env_list **env_list)
{
	t_env	*curr;
	t_env	*prev;

	if (!env_list || !*env_list)
		return ;
	curr = (*env_list)->bottom;
	while (curr)
	{
		prev = curr->prev;
		free_env(&curr);
		curr = prev;
	}
	free(*env_list);
	*env_list = NULL;
}

void	free_all(t_data *data, char **prompt)
{
	if (data->token_list)
		free_token_list(&data->token_list);
	if (data->env_list)
		free_env_list(&data->env_list);
	if (prompt && *prompt)
	{
		free(*prompt);
		*prompt = NULL;
	}
}
