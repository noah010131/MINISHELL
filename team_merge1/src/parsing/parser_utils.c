/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:27:56 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/18 16:06:30 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**free_pars_arguments(char **arguments)
{
	int	i;

	i = 0;
	if (!arguments || !*arguments)
		return (NULL);
	while (arguments[i])
	{
		if (arguments[i])
		{
			free(arguments[i]);
			arguments[i] = NULL;
		}
		i++;
	}
	if (arguments)
		free(arguments);
	return (NULL);
}

void	free_pars_list(t_pars **parsee)
{
	t_pars	*current_p;
	t_pars	*next_p;
	t_redir	*current_r;
	t_redir	*cache_r;

	if (!parsee || !*parsee)
		return ;
	current_p = *parsee;
	while (current_p)
	{
		current_r = current_p->redirections;
		next_p = current_p->next;
		free_pars_arguments(current_p->arguments);
		free(current_p);
		current_p = NULL;
		while (current_r)
		{
			cache_r = current_r->next;
			free(current_r->filename);
			free(current_r);
			current_r = cache_r;
		}
		current_p = next_p;
	}
	free(parsee);
}

void	add_last_par(t_pars **pars_list, t_pars *node)
{
	t_pars	*curr;

	if (!pars_list)
		pars_list = init_parser();
	if (!node)
		return ;
	if (!*pars_list)
	{
		*pars_list = node;
		return ;
	}
	curr = *pars_list;
	while (curr->next)
		curr = curr->next;
	curr->next = node;
}

/*void	add_last_par(t_pars **pars, t_pars *new) // origin
{
	t_pars	*current;

	if (!pars || !new)
		return ;
	new->next = NULL;
	if (!*pars)
	{
		*pars = new;
		return ;
	}
	current = *pars;
	while (current->next)
		current = current->next;
	current->next = new;
}*/

t_redir	*new_redir(t_type_redir type, char *filename)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	res->type = type;
	res->filename = ft_strdup(filename);
	res->next = NULL;
	return (res);
}

int	add_last_redir(t_redir *new, t_pars *pars)
{
	t_redir	*current;

	if (!pars || !new)
		return (1);
	if (!pars->redirections)
		pars->redirections = new;
	else
	{
		current = pars->redirections;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}
