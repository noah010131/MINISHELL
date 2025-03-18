/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:11:21 by princessj         #+#    #+#             */
/*   Updated: 2025/03/17 17:09:48 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser_check_print(t_pars **parser)
{
	int		i;
	int		j;
	t_pars	*curr;
	t_redir	*redir;

	if (!parser || !*parser)
	{
		ft_err_print_minishell("Error: Parser list is empty or uninitialized.");
		exit(EXIT_FAILURE);
	}
	i = 0;
	curr = *parser;
	ft_printf("\n========== Parser List ==========\n");
	while (curr)
	{
		ft_printf("[%d] Command: %s\n", i);
		if (curr->command)
			ft_printf("%s\n", curr->command);
		else
			ft_printf("NULL\n");
		j = 0;
		ft_printf("   Arguments: ");
		if (curr->arguments)
		{
			while (curr->arguments[j])
			{
				ft_printf("[%s] ", curr->arguments[j]);
				j++;
			}
			ft_printf("\n");
        }
		else
			ft_printf("NULL\n");
		redir = curr->redirections;
		if (!redir)
			ft_printf("   Redirections: NULL\n");
		else
		{	
			while (redir)
			{
				ft_printf("   Redirection Type: %d, File: %s\n",
					redir->type, redir->filename ? redir->filename : "NULL");
				redir = redir->next;
			}
		}
		ft_printf("   Next Command: ");
		if (curr->next)
			ft_printf("%s\n\n", curr->next->command);
		else
		ft_printf("NULL\n\n");
		curr = curr->next;
		i++;
	}
}

void	env_list_check_print(t_env_list *env_list)
{
	int		i;
	t_env	*curr;

	if (!env_list || !env_list->bottom || !env_list->top)
	{
		printf("Error: Env list is empty or uninitialized.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	curr = env_list->bottom;
	printf("Top key: %s, Bottom key: %s\n\n", env_list->top->key, curr->key);
	while (curr)
	{
		printf("key %d: %s\n", i, curr->key);
		if (curr->prev)
			printf("   prev: %s\n", curr->prev->key);
		else
			printf("   prev: NULL\n");
		if (curr->next)
			printf("   next: %s\n\n", curr->next->key);
		else
			printf("   next: NULL\n\n");
		curr = curr->prev;
		i++;
	}
}

void	token_list_check_print(t_token_list *token_list)
{
	int		i;
	t_token	*curr;

	if (!token_list || !token_list->bottom || !token_list->top)
	{
		printf("Error: Token list is empty or uninitialized.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	curr = token_list->bottom;
	printf("Token count: %d\n", token_list->cnt);
	printf("Top: %s, Bottom: %s\n\n", token_list->top->str,
		token_list->bottom->str);
	while (curr)
	{
		printf("%d: %s\n", i, curr->str);
		if (curr->prev)
			printf("   prev: %s\n", curr->prev->str);
		else
			printf("   prev: NULL\n");
		if (curr->next)
			printf("   next: %s\n\n", curr->next->str);
		else
			printf("   next: NULL\n\n");
		curr = curr->prev;
		i++;
	}
}

void	token_check_print(t_token *token)
{
	int	len;

	len = (int)ft_strlen(token->str);
	printf("token type : %d [%s], token str len : %d\n",
		token->type, token->str, len);
}
