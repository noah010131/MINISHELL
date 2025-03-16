/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:41:59 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/03 18:22:16 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*last;
	char	find;
	size_t	i;

	last = (char *)str;
	find = (char)c;
	i = ft_strlen(str);
	if ((char)c == '\0')
		return ((char *)(str + i));
	while (i > 0)
	{
		if (last[i] == find)
			return (last + i);
		i--;
	}
	if (last[i] == find)
		return (last);
	return (0);
}
/*
int	main(void)
{
	printf("%s\n", ft_strrchr("123456", '6'));
	return (0);
}
*/
