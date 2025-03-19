/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:23:35 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/08/30 03:56:05 by princessj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*new_s;

	if (s1 == NULL)
		s1 = ft_calloc_gnl(sizeof(char), 1);
	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	new_s = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new_s[s1_len + i] = s2[i];
		i++;
	}
	return (new_s[s1_len + s2_len] = '\0', free(s1), new_s);
}

int	ft_strchr_gnl(char *buffer, char n)
{
	int	i;

	i = 0;
	if (buffer == NULL)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == n)
			return (i);
		i++;
	}
	return (-1);
}

void	*ft_memset_gnl(void *ptr, int v, size_t c)
{
	char	*a;
	size_t	i;

	a = (char *)ptr;
	i = 0;
	while (i < c)
	{
		a[i] = (char)v;
		i++;
	}
	return (ptr);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	void	*temp;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	temp = malloc(count * size);
	if (temp == 0)
		return (0);
	temp = ft_memset_gnl(temp, 0, count);
	return (temp);
}
