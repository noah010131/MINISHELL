/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:47:58 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/05 15:28:54 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *sorce, size_t num)
{
	size_t	i;

	i = 0;
	if (!dest && !sorce)
		return (NULL);
	while (i < num)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)sorce)[i];
		++i;
	}
	return (dest);
}
/*
int	main(void)
{
	char	*a = "HELLO";
	const char	*b = "abcdef";

	ft_memcpy(a, b, sizeof(char)*3);
	printf("%s\n %s\n", a, b);
	return (0);
}
*/
