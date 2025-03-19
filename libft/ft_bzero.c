/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:32:22 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/05/28 18:33:37 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	*ft_memset(void *ptr, int v, size_t c)
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
*/

void	*ft_bzero(void *ptr, size_t len)
{
	ft_memset(ptr, 0, len);
	return (ptr);
}

/*
int	main(void)
{
	char	a[] = "aaaaa";

	ft_bzero(a, 3*sizeof(char));
	printf("%s\n", a);
	return (0);
}
*/
