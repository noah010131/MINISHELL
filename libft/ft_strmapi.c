/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princessj <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:28:47 by princessj         #+#    #+#             */
/*   Updated: 2024/06/04 15:06:18 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			s_len;
	char			*result;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (s_len + 1));
	if (result == NULL)
		return (NULL);
	while (i < s_len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[s_len] = '\0';
	return (result);
}
/*
char	ft_check_f(unsigned int i, char c)
{
	(void)i;
	return (c + 1);	
}	
int	main(void)
{
	char	*a;

	a = ft_strmapi("abcdefg", ft_check_f);
	printf("%s\n", a);
	return (0);
}*/
