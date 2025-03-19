/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princessj <princessj@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:42:29 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/08 03:38:50 by princessj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_c(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_format_s(char *s)
{
	int	i;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		write(1, s + i, 1);
		i++;
	}
	return (i);
}

int	ft_format_di(long di)
{
	int	count;

	count = 0;
	if (0 > di)
	{
		write (1, "-", 1);
		count++;
		di *= -1;
	}
	if (0 <= di && 9 >= di)
	{
		di += '0';
		write(1, &di, 1);
		count++;
	}
	else if (9 < di)
	{
		count += ft_format_di(di / 10);
		di = (di % 10) + '0';
		write(1, &di, 1);
		count++;
	}
	return (count);
}

int	ft_format_u(unsigned int u)
{
	int	count;

	count = 0;
	if (9 >= u)
	{
		u += '0';
		write(1, &u, 1);
		count++;
	}
	else if (9 < u)
	{
		count += ft_format_u(u / 10);
		u = (u % 10) + '0';
		write(1, &u, 1);
		count++;
	}
	return (count);
}

int	ft_format_x(unsigned long x, char *hexa)
{
	int	count;

	count = 0;
	if (x >= 16)
	{
		count += ft_format_x(x / 16, hexa);
		write(1, hexa + (x % 16), 1);
		count++;
	}
	else
	{
		write(1, hexa + x, 1);
		count++;
	}
	return (count);
}
