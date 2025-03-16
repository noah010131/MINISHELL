/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:02:56 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/13 23:46:10 by chanypar         ###   ########.fr       */
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

// ebauche d une fonction qui retourne la fin d une
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
