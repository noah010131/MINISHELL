/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:35:10 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/14 09:25:06 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	remove_isspace(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}
// idem a isprint mais pour un string entier
int	non_print2(char *str, char c)
{
	int	i;

	i = 0;

	i = remove_isspace(str);
	i = check_ch(str, c, i);
	while (str[i] && str[i] == c)
	{
		if (ft_isspace(str[i + 1]))
		{
			i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (str[i] == c)
				return (1);
		}
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}
int	non_print(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (non_print2(str, '<') || non_print2(str, '>'))
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] == '_' || str[i] == '\'' || str[i] == '"')
				return (0);
			if (str[i] == '$' || str[i] == ' ' || str[i] == '?')
				return (0);
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				return (0);
			if (str[i] == '-' || (str[i] == '.' && str[i + 1]) || str[i] == '/')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

// fonction qui verifie que chaque quote soit fermee
// 1 si ouverte
// 0 si fermee
// -1 si erreur

int	open_quote(char *str)
{
	int		flag;
	int		i;
	char	quote;

	flag = 0;
	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = 1;
			quote = str[i];
			i++;
			while ((str[i] != quote) && str[i])
				i++;
		}
		if (!str[i])
			return (flag);
		flag = 0;
		i++;
	}
	return (flag);
}

int	tok_acc(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while ((str[i] != quote) && str[i])
				i++;
		}
		if (is_token(str + i) == 1)
		{
			while (str[i] && is_token(str + i))
			{
				j++;
				i++;
			}
			if (j > 2)
				return (1);
			j = 0;
		}
		i++;
	}
	return (0);
}
