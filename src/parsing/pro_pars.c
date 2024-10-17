/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pro_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:03:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/04 18:55:11 by ihibti           ###   ########.fr       */
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

void	add_last_par(t_pars **pars, t_pars *new)
{
	t_pars	*current;

	if (!pars || !new)
		return ;
	if (!*pars)
	{
		*pars = new;
		return ;
	}
	current = *pars;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	keep_pars(t_pars *new, t_cmds *cmd)
{
	// if (cmd->next)
	//     printf("prealable : %s   %s\n", cmd->name, cmd->next->name);
	// else
	//     printf("prealable :    %s\n", cmd->name);
	if (cmd->code_id == WORD)
		return (add_arg(new, cmd->name));
	else if (cmd->code_id == REDIR_IN)
		return (add_last_redir(new_redir(REDIR_IN_S, cmd->next->name), new));
	else if (cmd->code_id == HEREDOC_IN)
		return (add_last_redir(new_redir(HEREDOC, cmd->next->name), new));
	else if (cmd->code_id == REDIR_OUT)
		return (add_last_redir(new_redir(REDIR_OUT_S, cmd->next->name), new));
	else if (cmd->code_id == REDIR_APP)
		return (add_last_redir(new_redir(REDIR_OUT_D, cmd->next->name), new));
	return (0);
}

char	**freee_error(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	add_arg(t_pars *pars, char *new)
{
	char	**ret;
	int		i;

	i = 0;
	while (pars->arguments && pars->arguments[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (1);
	i = 0;
	while (pars->arguments && pars->arguments[i])
	{
		ret[i] = ft_strdup(pars->arguments[i]);
		if (!ret[i])
			return (freee_error(ret), 1);
		i++;
	}
	ret[i++] = ft_strdup(new);
	ret[i] = 0;
	freee_error(pars->arguments);
	pars->arguments = ret;
	pars->command = ret[0];
	return (0);
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
