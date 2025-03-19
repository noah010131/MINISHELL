/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princessj <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:18:43 by princessj         #+#    #+#             */
/*   Updated: 2024/06/05 15:23:50 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_n(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len_n;
	long	nb;

	nb = (long)n;
	len_n = count_n(nb);
	result = (char *)malloc(sizeof(char) * (len_n + 1));
	if (result == 0)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		result[0] = '-';
	}
	result[len_n--] = '\0';
	while (nb > 9)
	{
		result[len_n--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	result[len_n] = nb + '0';
	return (result);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(200));
	return (0);
}*/
