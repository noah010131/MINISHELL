/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:59:21 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 05:02:50 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*int		add_arg(t_pars *pars_node, char *token_str) // 수정해야함
{
	int		i;
	char	*result;

	i = 0;
	if (!token_str || !token_str[i])
		return (0);
	result = (char *)malloc(sizeof(char *) * ft_strlen(token_str) + 1);
	if (!result)
		return (ft_malloc_fail("add arg: result"), ERR);
	result = ft_strdup(token_str);
	if (!result)
		return (ft_malloc_fail("add arg: result ft_strdup"), ERR);
	while (pars_node->arguments && pars_node->arguments[i])
		i++;
	pars_node->arguments[i] = result;
	pars_node->command = result;
	return (0);
}*/

int	add_arg(t_pars *pars_node, char *token_str) //origin
{
	char	**ret;
	int		i;

	i = 0;
	while (pars_node->arguments && pars_node->arguments[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (ft_err_print_minishell("add arg: ret"), ERR);
	i = 0;
	while (pars_node->arguments && pars_node->arguments[i])
	{
		ret[i] = ft_strdup(pars_node->arguments[i]);
		if (!ret[i])
			return (free_pars_arguments(ret), 1);
		i++;
	}
	ret[i++] = ft_strdup(token_str);
	ret[i] = 0;
	free_pars_arguments(pars_node->arguments);
	pars_node->arguments = ret;
	pars_node->command = ret[0];
	return (0);
}

int	keep_pars(t_pars *pars_node, t_token *token)
{
	if (token->type == W || token->type == DQ || token->type == SQ)
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

void	pars_state(t_pars *pars_node, t_token *token_curr, t_pars **pars_list)
{
	while (token_curr && token_curr->type != P)
	{
		if (keep_pars(pars_node, token_curr))
				free_pars_list(pars_list);
		if (token_curr->prev)
		{
			if (token_curr->type != W)
				token_curr = token_curr->prev;
		}
		token_curr = token_curr->prev;
	}
	//return (pars_node);
}

/*t_token	*pars_state(t_pars *pars_node, t_token *token_curr, t_pars **pars_list) // origin
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
}*/

t_pars	**change_struct(t_token_list *token_list)
{
	t_token	*token_curr;
	t_pars	*pars_node;
	t_pars	**pars_list;

	pars_list = init_parser();
	token_curr = token_list->bottom;
	if (token_curr)
	{
		pars_node = init_pars_node();
		if (!pars_node)
			return (free_pars_list(pars_list), NULL); // 추후 체크
		pars_state(pars_node, token_curr, pars_list);
		add_last_par(pars_list, pars_node);
		if (token_curr)
			token_curr = token_curr->prev;
	}
	return (pars_list);
}

/*t_pars	**change_struct(t_token_list *token_list) // ORIGIN
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
		init_pars_node();
		//pars_node = pars_state(pars_node, token_curr, pars_list);
		pars_state(pars_node, token_curr, pars_list);
		add_last_par(pars_list, pars_node);
		if (token_curr)
			token_curr = token_curr->prev;
	}
	return (pars_list);
}*/
