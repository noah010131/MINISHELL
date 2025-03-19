/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:26:41 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/17 13:04:58 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	newline_syntax_check(t_token *first)
{
	if (!first)
		return (0);
	if (first->type == AR || first->type == RO || first->type == RI
		|| first->type == H || first->type == P)
	{
		ft_syntax_err("newline");
		return (ERR);
	}
	return (0);
}

int	redirect_syntax_check(t_token *first, t_token *second)
{
	if (!first || !second)
		return (0);
	if (second->type == AR || second->type == RO || second->type == RI
		|| second->type == H)
	{
		if (first->type == AR || first->type == RO || first->type == RI
			|| first->type == H)
		{
			ft_syntax_err(second->str);
			return (ERR);
		}
	}
	return (0);
}

int	pipe_syntax_check(t_token *first, t_token *second)
{
	if (!first || !second)
		return (0);
	if (second->type == P)
	{
		if (first->type == P || first->type == AR || first->type == RO
			|| first->type == RI || first->type == H)
		{
			ft_syntax_err(second->str);
			return (ERR);
		}
	}
	return (0);
}

int	syntax_check(t_token_list *token_list)
{
	t_token	*token_start;
	t_token	*first_token;
	t_token	*second_token;

	if (!token_list || !token_list->bottom)
		return (0);
	token_start = token_list->bottom;
	first_token = token_start;
	second_token = first_token->prev;
	while (second_token)
	{
		if (pipe_syntax_check(first_token, second_token) == ERR
			|| redirect_syntax_check(first_token, second_token) == ERR)
			return (ERR);
		first_token = second_token;
		second_token = first_token->prev;
	}
	if (newline_syntax_check(first_token) == ERR)
		return (ERR);
	return (0);
}
