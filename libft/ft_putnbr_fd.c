/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: princessj <princessj@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:00:58 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/08 03:37:57 by princessj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = (long)n;
	if (0 > nb)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (0 <= nb && 9 >= nb)
	{
		nb += '0';
		write(fd, &nb, 1);
	}
	else if (9 < nb)
	{
		ft_putnbr_fd(nb / 10, fd);
		nb = (nb % 10) + '0';
		write(fd, &nb, 1);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(42, 1);
	return (0);
}
*/
