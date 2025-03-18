/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:18:41 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/03 15:55:14 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	j;

	i = 0;
	j = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	while (str[i] != 0 && (str[i] >= 48 && str[i] <= 57))
	{
		j = j * 10 + (str[i] - '0');
		i++;
	}
	return (j * signe);
}
/*
int	main(void)
{
	const char	*a = "\t\n\r\v\f  469 \n";

	printf("%d\n", ft_atoi(a));
	return (0);
}
*/
