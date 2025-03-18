/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:52:57 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/17 18:27:23 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*init_token(void)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
	{
		ft_malloc_fail("init token");
		return (NULL);
	}
	tmp->str = NULL;
	tmp->type = 0;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_env	*init_envp(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
	{
		ft_malloc_fail("init envp");
		return (NULL);
	}
	env->key = NULL;
	env->value = NULL;
	env->origin_env = NULL;
	env->next = NULL;
	env->prev = NULL;
	return (env);
}

void	init_env_list(t_env_list **env_list)
{
	*env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!(*env_list))
	{
		ft_malloc_fail("init env list");
		exit(EXIT_FAILURE);
	}
	(*env_list)->flag = 0;
	(*env_list)->top = NULL;
	(*env_list)->bottom = NULL;
}

void	init_token_list(t_token_list **token_list)
{
	*token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!(*token_list))
	{
		ft_malloc_fail("init token list");
		exit(EXIT_FAILURE);
	}
	(*token_list)->cnt = 0;
	(*token_list)->open_quote_flag = 0;
	(*token_list)->top = NULL;
	(*token_list)->bottom = NULL;
}

void	init_data(t_data *data, int arc, char **argv)
{
	(void)arc;
	(void)argv;
	data->prompt = NULL;
	init_token_list(&data->token_list);
	init_env_list(&data->env_list);
}
