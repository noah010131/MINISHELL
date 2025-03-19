/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:47:52 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/05/29 12:40:39 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t element_count, size_t element_size)
{
	int	*temp;

	if (element_size > 0 && element_count > SIZE_MAX / element_size)
		return (NULL);
	temp = malloc(element_count * element_size);
	if (temp == 0)
		return (0);
	ft_memset(temp, 0, element_size * element_count);
	return (temp);
}

/*
int	main(void)
{
	printf("%\n", ft_calloc());
	return (0);
}
*/
