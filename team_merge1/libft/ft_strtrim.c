/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:48:33 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/04 21:56:08 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_if_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (check_if_set(set, s1[i]))
		i++;
	return (i);
}

int	check_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (check_if_set(set, s1[i - 1]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;
	int		re_len;
	int		i;

	i = 0;
	if (set[0] == 0)
		return (ft_strdup((char *)s1));
	start = check_start(s1, set);
	if (s1[start] == '\0')
		return (ft_strdup(""));
	end = check_end(s1, set);
	re_len = end - start;
	result = (char *)malloc(sizeof(char) * (re_len + 1));
	if (!s1 || !result)
		return (NULL);
	while (start < end)
	{
		result[i] = s1[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim("hello", ""));
	return (0);
}*/
