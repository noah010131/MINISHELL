/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:45:30 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/13 23:45:55 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*end_quote(char *str, char c)
{
	int		i;
	int		j;
	int		count;
	char	*ret;

	ret = malloc(ft_strlen(str) + 1);
	if (!str || !ret)
		return (pers_free(ret), NULL);
	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		ret[j++] = str[i];
		if (count == 2)
		{
			ret[j] = 0;
			return (ret);
		}
		i++;
	}
	return (pers_free(ret), NULL);
}

int	go_last_lex(char *str, int i, int j)
{
	if (is_token(str + i + j))
	{
		while (str[i + j] && (str[i + j] == str[i]))
			j++;
		return (j);
	}
	while (str[i + j] && !ft_isspace(str[i + j]) && !is_token(str + i + j))
	{
		if (str[i + j] == '\'' || str[i + j] == '"')
			j = n_end_quote(str, i, j) + 1;
		else
			j++;
	}
	return (j);
}

int	is_token(char *str)
{
	if (!str)
		return (-1);
	if (!*str)
		return (-1);
	if (ft_strncmp("<<", str, 2) == 0 || ft_strncmp(">>", str, 2) == 0)
		return (1);
	if (ft_strncmp("<", str, 1) == 0 || ft_strncmp(">", str, 1) == 0)
		return (1);
	if (ft_strncmp("|", str, 1) == 0)
		return (1);
	return (0);
}

int	n_end_quote(char *str, int i, int j)
{
	char	c;

	c = str[i + j];
	j++;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

void	free_tcmd(t_cmds **cmds)
{
	t_cmds	*current;
	t_cmds	*tmp;

	if (!cmds)
		return ;
	if (!*cmds)
	{
		free(cmds);
		return ;
	}
	current = *cmds;
	while (current)
	{
		tmp = current->next;
		free(current->name);
		free(current);
		current = tmp;
	}
	free(cmds);
}