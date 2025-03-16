/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:53:30 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 16:53:31 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	merge_token_node(t_token *token_a, t_token *token_b, t_token_list *list)
{
	token_a->prev = token_b->prev;
	if (token_b->prev)
		token_b->prev->next = token_a;
	free_token(&token_b);
	token_b = NULL;
	list->cnt--;
	if (!token_a->prev)
		list->top = token_a;
}

void	merge_token_str(t_token_list *token_list)
{
	t_token	*first_token;
	t_token	*second_token;
	char	*merge_str;

	if (!token_list || !token_list->bottom)
		ft_err_print_minishell("no tokens");
	first_token = token_list->bottom;
	while (first_token && first_token->prev)
	{
		second_token = first_token->prev;
		if (first_token && second_token
			&& (first_token->type == W || first_token->type == SQ
				|| first_token->type == DQ) && (second_token->type == W
				|| second_token->type == SQ || second_token->type == DQ))
		{
			merge_str = ft_strjoin(first_token->str, second_token->str);
			if (!merge_str)
				ft_malloc_fail("merge token str");
			free(first_token->str);
			first_token->str = merge_str;
			merge_token_node(first_token, second_token, token_list);
			continue ;
		}
		first_token = first_token->prev;
	}
}
