/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:17:05 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/04 15:03:45 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	ft_check(unsigned int i, char *c)
{
	(void)i;
	write(1, c, 1);
}

int	main(void)
{
	char *a = "aaaa";

	ft_striteri(a, ft_check);
	//printf("%s\n", a);
	return (0);
}*/
