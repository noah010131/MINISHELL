/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:10:05 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/03 22:14:22 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	s1_len;
	size_t	s2_len;
	int		i;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s = (char *)malloc(sizeof(char) * ((s1_len + s2_len) + 1));
	if (new_s == 0)
		return (NULL);
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
	new_s[s1_len + i] = '\0';
	return (new_s);
}
/*
int	main(void)
{
	char	*a = ft_strjoin(ft_strjoin("My favorite animal is", " "), "Jihye");
	printf("%s\n", a);
	return (0);
}*/
