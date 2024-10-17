/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:58:17 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/04 19:12:43 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (ft_strlen(second) > (int)length)
		return (1);
	while ((i < length) && (first[i] || second[i]))
	{
		if (first[i] != second[i])
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i += 1;
	}
	return (0);
}

t_envp	*env_match(char *str, t_envp **lst)
{
	int		i;
	t_envp	*current;

	i = 0;
	if (!str || !str[0] || !lst || !*lst)
		return (NULL);
	if (str[i] == '?')
		return (NULL);
	while (str[i] && is_lim_exp(str[i]) == 0)
		i++;
	current = *lst;
	while (current)
	{
		if (ft_stricmp(str, current->name, i) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
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