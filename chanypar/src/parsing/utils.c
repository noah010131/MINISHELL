/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:02:56 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/29 15:23:01 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// retourne le nombre d'occurences du char passe en
// parametre -1 si il y a une erreur

int	ft_occur(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

// ebauche d une fonction qui retorune la fin d une
// quote mais a revoir

char	*quote_tok(char *str, int *ind, char quote)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (*ind < 0)
		return (NULL);
	while (str[*ind + i])
	{
		if (str[*ind + i] == quote)
			return (*ind += i, ft_strlimdup(&str[*ind], i));
		i++;
	}
	return (NULL);
}

// retourne la premiere occurence d un
// char dans une string
// -2 si erreur -1 si pas trouve
int	ft_pos_c(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-2);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	pers_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

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
