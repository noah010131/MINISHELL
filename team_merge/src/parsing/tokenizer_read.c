/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:53:53 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/17 12:42:51 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_really_special(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '"')
		return (true);
	return (false);
}

char	*read_word(char **cmd, char stop)
{
	int		i;
	char	*start;
	char	*result;

	i = 0;
	start = *cmd;
	result = NULL;
	if (!cmd || !*cmd || !**cmd)
		return (result);
	while ((*cmd)[i] && (*cmd)[i] != stop)
	{
		if (is_really_special((*cmd)[i]))
			break ;
		i++;
	}
	result = ft_strndup(start, i);
	if (!result)
		ft_malloc_fail("read word");
	*cmd += i;
	return (result);
}

char	*read_only_space(char **cmd, char space)
{
	int		i;
	char	*start;
	char	*result;

	i = 0;
	start = *cmd;
	result = NULL;
	if (!cmd || !*cmd || !**cmd)
		return (result);
	while ((*cmd)[i] && (*cmd)[i] == space)
		i++;
	result = ft_strndup(start, i);
	if (!result)
		ft_malloc_fail("read only space");
	*cmd += i;
	return (result);
}

char	*read_until_quote(char **cmd, char stop_quote, t_data *data)
{
	int		i;
	char	*start;
	char	*result;

	if (!cmd || !*cmd || !**cmd)
		return (NULL);
	i = 0;
	start = *cmd;
	result = NULL;
	if ((*cmd)[i] == stop_quote)
	{
		i++;
		start++;
		while ((*cmd)[i] && (*cmd)[i] != stop_quote)
			i++;
		if ((*cmd)[i] == stop_quote)
		{
			result = ft_strndup(start, (i - 1));
			*cmd += (i + 1);
			return (result);
		}
	}
	open_quote(data);
	return (NULL);
}
