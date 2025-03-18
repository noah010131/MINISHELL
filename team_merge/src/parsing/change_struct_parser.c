/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_struct_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:59:21 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/18 02:33:12 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_arg(t_pars *pars, char *token_str)
{
	char	**ret;
	int		i;

	i = 0;
	while (pars->arguments && pars->arguments[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (ft_err_print_minishell("add arg: ret"), ERR);
	i = 0;
	while (pars->arguments && pars->arguments[i])
	{
		ret[i] = ft_strdup(pars->arguments[i]);
		if (!ret[i])
			return (free_pars_arguments(ret), 1);
		i++;
	}
	ret[i++] = ft_strdup(token_str);
	ret[i] = 0;
	free_pars_arguments(pars->arguments);
	pars->arguments = ret;
	pars->command = ret[0];
	return (0);
}

int	keep_pars(t_pars *pars_node, t_token *token)
{
	if (token->type == W)
		return (add_arg(pars_node, token->str));
	else if (token->type == RI)
		return (add_last_redir(new_redir(REDIR_IN_S, token->prev->str), pars_node));
	else if (token->type == H)
		return (add_last_redir(new_redir(HEREDOC, token->prev->str), pars_node));
	else if (token->type == RO)
		return (add_last_redir(new_redir(REDIR_OUT_S, token->prev->str), pars_node));
	else if (token->type == AR)
		return (add_last_redir(new_redir(REDIR_OUT_D, token->prev->str), pars_node));
	return (0);
}

int	keep_pars2(t_pars *new, t_cmds *cmd)
{
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

t_token	*pars_state(t_pars *pars_node, t_token *token_curr, t_pars **pars_list)
{
	while (token_curr && token_curr->type != P)
	{
		if (keep_pars(pars_node, token_curr))
			return (free_pars_list(pars_list), NULL);
		if (token_curr->prev)
		{
			if (token_curr->type != W)
				token_curr = token_curr->prev;
		}
		token_curr = token_curr->prev;
	}
	return (token_curr);
}

t_pars	**change_struct(t_token_list *token_list)
{
	t_token	*token_curr;
	t_pars	*pars_node;
	t_pars	**pars_list;

	pars_list = init_parser();
	token_curr = token_list->bottom;
	while (token_curr)
	{
		pars_node = (t_pars *)malloc(sizeof(t_pars));
		if (!pars_node)
			return (free_pars_list(pars_list), NULL);
		init_pars_node(pars_node);
		token_curr = pars_state(pars_node, token_curr, pars_list);
		add_last_par(pars_list, pars_node);
		if (token_curr)
			token_curr = token_curr->prev;
	}
	return (pars_list);
}
