/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:55:47 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 10:34:00 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*add_token_special(char *cmd, int type)
{
	t_token	*new_token;

	new_token = NULL;
	new_token = init_token();
	new_token->str = ft_strdup(cmd);
	if (!new_token->str)
	{
		free(new_token);
		new_token = NULL;
		return (NULL);
	}
	new_token->type = type;
	return (new_token);
}

t_token	*add_token(char *cmd, int type)
{
	t_token	*new_token;

	new_token = NULL;
	new_token = init_token();
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

t_token	*add_special_token(char **cmd, char *symbol, int type, int step)
{
	*cmd += step;
	return (add_token_special(symbol, type));
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

void	tokenizer(char *cmd, t_data *data)
{
	t_token	*new_token;

	new_token = NULL;
	while (cmd && *cmd && find_space(*cmd))
		cmd++;
	while (cmd && *cmd)
	{
		new_token = is_special(&cmd);
		if (new_token)
		{
			add_token_list_node(new_token, data->token_list);
			continue ;
		}
		else if (*cmd == '\'')
			new_token = add_token(read_until_quote(&cmd, '\'', data), SQ);
		else if (*cmd == '"')
			new_token = add_token(read_until_quote(&cmd, '"', data), DQ);
		else if (*cmd == ' ')
			new_token = add_token(read_only_space(&cmd, ' '), S);
		else
			new_token = add_token(read_word(&cmd, ' '), W);
		if (!new_token && data->token_list->open_quote_flag == ERR)
			return ;
		add_token_list_node(new_token, data->token_list);
	}
}
