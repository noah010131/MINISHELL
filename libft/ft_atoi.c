/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:32:20 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/13 16:26:18 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	i;
	long long	minus;
	long long	somme;

	minus = 1;
	somme = 0;
	i = 0;
	while ((((str[i] <= 13) && (str[i] >= 9)) || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
		somme = (somme * 10) + (str[i++] - '0');
	if (somme == 0)
		return (0);
	return (somme * minus);
}
