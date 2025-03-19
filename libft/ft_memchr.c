/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:39:07 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/05/28 18:39:13 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	*ft_memchr(const void *ptr, int v, size_t n)
{
	char	find;
	int	i;

	find = (char)v;
	if (n == 0)
		return (NULL);
	while ((char *)ptr && n > 0)
	{
		if (find == (char)ptr[i])
			return (*ptr);
		n--;
		i++;
	}
	return (NULL);
}
*/

void	*ft_memchr(const void *ptr, int v, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (((unsigned char *)ptr)[i] == (unsigned char)v)
			return ((void *)ptr + i);
		i++;
	}
	return ((void *)0);
}

/*
int	main(void)
{
	char	*a = "abcd";
	char	*b;

	b = (char *)ft_memchr(a, 'c', 4);
	printf("%s\n", b);
	return (0);
}
*/
