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

t_cmds	*pars_state(t_pars *new, t_cmds *current, t_pars **ret)
{
	while (current && current->code_id != PIPE_N)
	{
		if (keep_pars(new, current))
			return (free_pars_ls(ret), NULL);
		if (current->code_id != WORD)
			current = current->next;
		current = current->next;
	}
	return (current);
}

t_pars	**parser(t_cmds **cmds)
{
	t_cmds	*current;
	t_pars	*new;
	t_pars	**ret;

	ret = malloc(sizeof(t_pars));
	if (!ret)
		return (NULL);
	*ret = NULL;
	current = *cmds;
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