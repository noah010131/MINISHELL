/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:57:14 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/17 20:55:50 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_pars_node(t_pars *parse_node)
{
	if (!parse_node)
		return ;
	parse_node->arguments = NULL;
	parse_node->command = NULL;
	parse_node->next = NULL;
	parse_node->redirections = NULL;
}

t_pars	**init_parser(void)
{
	t_pars	**result;
	
	result = (t_pars **)malloc(sizeof(t_pars));
	if (!result)
		return (ft_malloc_fail("init parser"), NULL);
	(*result) = NULL;
	return (result);
}