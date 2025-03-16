/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:50:07 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 19:46:05 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_token_list_node(t_token *new_token, t_token_list *token_list)
{
	if (!new_token)
		ft_err_print_minishell("add token list node: No tokens");
	if (!token_list)
	{
		ft_err_print_minishell("Attempting to use a freed token list.");
		return ;
	}
	if (!token_list->top)
	{
		token_list->top = new_token;
		token_list->bottom = new_token;
		token_list->cnt++;
		return ;
	}
	else
	{
		new_token->next = token_list->top;
		token_list->top->prev = new_token;
		if (!token_list->bottom->prev)
			token_list->bottom->prev = new_token;
		token_list->top = new_token;
		token_list->cnt++;
	}
}

t_env_list	*add_env_list_node(t_env *new_env, t_env_list *env_list)
{
	if (!new_env)
		return (env_list);
	if (!env_list)
	{
		ft_err_print_minishell("add env list node");
		exit(EXIT_FAILURE);
	}
	if (!env_list->top)
	{
		env_list->top = new_env;
		env_list->bottom = new_env;
	}
	else
	{
		new_env->next = env_list->top;
		env_list->top->prev = new_env;
		env_list->top = new_env;
		if (!env_list->bottom->prev)
			env_list->bottom->prev = new_env;
	}
	return (env_list);
}
