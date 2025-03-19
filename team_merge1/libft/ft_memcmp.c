/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:22:58 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/03 18:39:50 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)ptr1;
	b = (unsigned char *)ptr2;
	i = 0;
	while (i < num)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*a = "abcdef";
	char	*b = "abc\375xx";

	printf("%d\n", ft_memcmp(a, b, 5));
	return (0);
}*/
