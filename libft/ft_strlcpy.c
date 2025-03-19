/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:42:38 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/04 21:49:32 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	temp;

	i = 0;
	temp = ft_strlen(src);
	if (dst == 0 || src == 0)
		return (0);
	while (i < temp && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (temp);
}
/*
int	main(void)
{
	char	dest[20] = "HELLO";
	char	*a = "world";

	printf("%zu\n", ft_strlcpy(dest, a, 3));
	printf("%s\n", dest);
	return (0);
}*/
