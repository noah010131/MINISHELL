/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:37:05 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/05/28 18:49:02 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		c += 32;
	return (c);
}

/*
int	main(void)
{
	printf("%c\n", ft_tolower('C'));
	printf("%d\n", ft_tolower('C'));
	return (0);
}
*/
