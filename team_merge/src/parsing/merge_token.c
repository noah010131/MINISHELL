/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:53:30 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/18 02:30:11 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	merge_token_node(t_token *first, t_token *sec, t_token_list *list)
{
	first->prev = sec->prev;
	if (sec->prev)
		sec->prev->next = first;
	if((first->type == SQ || first->type == DQ || first->type == W)
	&& (sec->type == SQ || sec->type == DQ || sec->type == W))
		first->type = W;
	free_token(&sec);
	sec = NULL;
	list->cnt--;
	if (!first->prev)
		list->top = first;
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
