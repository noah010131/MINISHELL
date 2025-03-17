/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:08:52 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 08:53:52 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen1(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;
	char	*res;

	len_s1 = ft_strlen1(s1);
	len_s2 = ft_strlen1(s2);
	str = (char *)malloc(len_s1 + len_s2 + 1);
	if (!str)
		return (0);
	res = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (s[0] == '\0')
		return (0);
	str = (char *)s;
	while (*str != c && *str != 0)
		str++;
	if (*str == c)
		return (str);
	return (NULL);
}

void	*ft_calloc(size_t nmenb, size_t size)
{
	char	*res;
	int		s;
	int		i;

	s = nmenb * size;
	res = malloc(s);
	if (!res)
		return (NULL);
	i = 0;
	while (i < s)
	{
		res[i] = '\0';
		i++;
	}
	return (res);
}
