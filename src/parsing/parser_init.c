/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:57:14 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 11:10:40 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_pars	*init_pars_node(void)
{
	t_pars	*new;

	new = (t_pars *)malloc(sizeof(t_pars));
	if (!new)
		return (ft_malloc_fail("ini pars node"), NULL);
	new->arguments = NULL;
	new->command = NULL;
	new->next = NULL;
	new->redirections = NULL;
	return (new);
}

/*void	init_pars_node(t_pars *parse_node)
{
	if (!parse_node)
		return ;
	parse_node->arguments = NULL;
	parse_node->command = NULL;
	parse_node->next = NULL;
	parse_node->redirections = NULL;
}*/

t_pars	**init_parser(void)
{
	t_pars	**result;

	result = (t_pars **)malloc(sizeof(t_pars));
	if (!result)
		return (ft_malloc_fail("init parser"), NULL);
	(*result) = NULL;
	return (result);
}
