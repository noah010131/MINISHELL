/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:55:47 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 22:04:35 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*add_token(char *cmd, int type)
{
	t_token	*new_token;

	new_token = NULL;
	new_token = init_token();
	if (!new_token)
		return (NULL);
	new_token->str = cmd;
	if (!new_token->str)
	{
		free(new_token);
		new_token = NULL;
		return (NULL);
	}
	new_token->type = type;
	return (new_token);
}

bool	is_really_special(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '"')
		return (true);
	return (false);
}

t_token	*add_special_token(char **cmd, char *symbol, int type, int step)
{
	*cmd += step;
	return (add_token(symbol, type));
}

t_token	*is_special(char **cmd)
{
	if (**cmd == '>')
	{
		if ((*cmd)[1] == '>')
			return (add_special_token(cmd, ">>", AR, 2));
		else
			return (add_special_token(cmd, ">", RO, 1));
	}
	else if (**cmd == '<')
	{
		if ((*cmd)[1] == '<')
			return (add_special_token(cmd, "<<", H, 2));
		else
			return (add_special_token(cmd, "<", RI, 1));
	}
	else if (**cmd == '|')
		return (add_special_token(cmd, "|", P, 1));
	return (NULL);
}

void	tokenizer(char *cmd, t_token_list *token_list)
{
	t_token	*new_token;

	new_token = NULL;
	while (*cmd && find_space(*cmd))
		cmd++;
	while (*cmd)
	{
		new_token = is_special(&cmd);
		if (new_token)
		{
			add_token_list_node(new_token, token_list);
			continue ;
		}
		else if (*cmd == '\'')
			new_token = add_token(read_until_quote(&cmd, '\''), SQ);
		else if (*cmd == '"')
			new_token = add_token(read_until_quote(&cmd, '"'), DQ);
		else if (*cmd == ' ')
			new_token = add_token(read_only_space(&cmd, ' '), S);
		else
			new_token = add_token(read_word(&cmd, ' '), W);
		if (!new_token)
			ft_malloc_fail("tokenizer: new token");
		add_token_list_node(new_token, token_list);
	}
}
