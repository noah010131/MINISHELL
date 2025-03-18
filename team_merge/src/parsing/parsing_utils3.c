/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:39:42 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/18 01:29:31 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t' || c == '\n')
		return (1);
	if (c == 0)
		return (-1);
	return (0);
}

char	*ft_strlimdup(char *str, int lim)
{
	char	*ret;

	if (!str || !str[0])
		return (NULL);
	ret = ft_strdup(str);
	if (!str)
		return (NULL);
	if (lim >= (int)ft_strlen(ret))
		return (ret);
	ret[lim] = 0;
	return (ret);
}

int	check_ch(char *str, char checker, int i)
{
	int	save_i;

	save_i = i;
	while (str[i])
	{
		if (str[i] == checker)
			return (i);
		i++;
	}
	return (save_i);
}