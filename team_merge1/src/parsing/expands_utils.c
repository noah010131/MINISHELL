/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:58:17 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/19 11:09:20 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_lim_exp(char c)
{
	if (c == ' ')
		return (1);
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

int	ft_stricmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	if (ft_strlen(second) > length)
		return (1);
	while ((i < length) && (first[i] || second[i]))
	{
		if (first[i] != second[i])
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i += 1;
	}
	return (0);
}

void	init_0(int *i, int *j)
{
	*i = 0;
	if (j)
		*j = 0;
}

int	interpret(char *str, char *ptr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i] && str + i != ptr)
	{
		if (str[i] == '"')
			flag = -flag;
		i++;
	}
	return (flag);
}

void	init_1(int *i, int *j, t_cmds ***ret)
{
	*i = 0;
	if (j)
		*j = 0;
	*ret = malloc(sizeof(t_cmds *));
}
