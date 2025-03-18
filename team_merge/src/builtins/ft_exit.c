/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:41:41 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/18 00:01:17 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

static int	atoi_for_exit(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					pn;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || \
		(pn == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

int	check_arg(char *arg)
{
	long long		number;
	int				error;

	number = 0;
	error = 0;
	number = atoi_for_exit(arg, &error);
	if (error)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		return (2);
	}
	return (number);
}

int	ft_exit(t_pars *cmd)
{
	int			rv;

	rv = 0;
	if (cmd->arguments && cmd->arguments[0] && !cmd->arguments[1])
		return (0);
	else if (cmd->arguments && cmd->arguments[0] && cmd->arguments[1])
	{
		if (cmd->arguments[2])
		{
			ft_putstr_fd("exit: too many arguments", 2);
			return (-1);
		}
		rv = check_arg(cmd->arguments[1]);
	}
	return (rv);
}
