/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:50:56 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/05/28 18:41:04 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int v, size_t c)
{
	char	*ptr2;
	size_t	i;

	ptr2 = (char *)ptr;
	i = 0;
	while (i < c)
	{
		ptr2[i] = (char)v;
		i++;
	}
	return (ptr);
}

/*
int	main(void)
{
	char	a[] = "aaaa";
	
	ft_memset(a, 'x', 2*sizeof(char));
	printf("%s\n", a);
	return (0);
}
*/
