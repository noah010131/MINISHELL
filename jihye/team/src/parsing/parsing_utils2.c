/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:37:06 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/13 23:38:36 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_pars_ls(t_pars **parsee)
{
	t_pars	*current_p;
	t_pars	*cache_p;
	t_redir	*current_r;
	t_redir	*cache_r;

	if (!parsee)
		return ;
	current_p = *parsee;
	while (current_p )
	{
		current_r = current_p->redirections;
		cache_p = current_p->next;
		freee_error(current_p->arguments);
		free(current_p);
		while (current_r)
		{
			cache_r = current_r->next;
			free(current_r->filename);
			free(current_r);
			current_r = cache_r;
		}
		current_p = cache_p;
	}
	free(parsee);
}

t_redir	*new_redir(t_type_redir type, char *filename)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	res->type = type;
	res->filename = ft_strdup(filename);
	res->next = NULL;
	return (res);
}

static void	pars_0(t_pars *new)
{
	if (!new)
		return ;
	new->arguments = NULL;
	new->command = NULL;
	new->next = NULL;
	new->redirections = NULL;
}

t_token	*pars_state(t_pars *new, t_token *current, t_pars **ret)
{
	while (current && current->type != PIPE_N)
	{
		if (keep_pars(new, current))
			return (free_pars_ls(ret), NULL);
		if (current->next && current->type != WORD)
			current = current->next;
		current = current->next;
	}
	return (current);
}

t_pars	**parser(t_token_list *list)
{
	t_token	*current;
	t_pars	*new;
	t_pars	**ret;

	ret = malloc(sizeof(t_pars));
	if (!ret)
		return (NULL);
	*ret = NULL;
	current = list->top;
	while (current)
	{
		new = malloc(sizeof(t_pars));
		if (!new)
			return (free_pars_ls(ret), NULL);
		pars_0(new);
		current = pars_state(new, current, ret);
		add_last_par(ret, new);
		if (current)
			current = current->next;
		new = NULL;
	}
	return (ret);
}