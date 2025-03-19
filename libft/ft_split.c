/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princessj <princessj@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:14:27 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/08 03:36:59 by princessj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	cnt_word(char const *s, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
			i -= 1;
		}
		i++;
	}
	return (cnt);
}

void	free_split(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	int		index;

	i = 0;
	index = 0;
	result = (char **)malloc(sizeof(char *) * (cnt_word(s, c) + 1));
	if (!result || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == 0)
			break ;
		result[index] = (char *)malloc(sizeof(char) * (wlen(s + i, c) + 1));
		if (result[index] == NULL)
			return (free_split(result), NULL);
		ft_strlcpy(result[index++], s + i, wlen(s + i, c) + 1);
		i += wlen(s + i, c);
	}
	result[index] = NULL;
	return (result);
}
/*
int	main(void)
{
	char	*a = "           ";
	char	**b = ft_split(a, ' ');
	int	i = 0;

	while (b[i])
	{
		printf("%s\n", b[i]);
		free(b[i]);
		i++;
	}
	return (0);
}

",,,jihye,est,super,bitch"
','
res_len = cnt_word(s, c); 
**a = (char **)malloc(res_len + 1) -> 0 1 2 3 4
(char *)malloc(6) <- "jihye" [0]
(char *)malloc(4) <- "est" [1]
(char *)malloc(6) <- "super" [2]
(char *)malloc(6) <- "bitch" [3]
NULL [4]
["jihye\0", "est\0", "super\0", "bitch\0", NULL]*/
