/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:29:46 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/03 22:01:50 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*result;
	size_t	re_len;
	size_t	i;

	i = 0;
	len_s = ft_strlen(s);
	if (len <= 0 || start >= len_s)
		return (ft_calloc(1, 1));
	re_len = len_s - start;
	if (re_len > len)
		re_len = len;
	result = (char *)malloc(sizeof(char) * (re_len + 1));
	if (result == NULL)
		return (NULL);
	while (s[start] && i < re_len)
		result[i++] = s[start++];
	result[i] = '\0';
	return (result);
}

/*
int	main(void)
{
	char const	*a = "Helloww";
	unsigned int	b = 0;
	size_t	c = 4; 

	printf("%s\n", ft_substr(a, b, c));
	return (0);
}
*/
