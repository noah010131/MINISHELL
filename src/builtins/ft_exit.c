/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:41:41 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/03 15:01:31 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_numeric(char	*arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
		{
			i++;
			continue ;
		}
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_arg(char *arg)
{
	int		i;

	i = 0;
	if (ft_atoi(arg) == -1 || check_numeric(arg))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	while (arg[i] && ((arg[i] >= '0' && arg[i] <= '9')
			|| (arg[0] == '+' || arg[0] == '-')))
		i++;
	if (!arg[i])
	{
		i = ft_atoi(arg);
		if (i < 0)
			i = 256 + i;
		else if (i > 256)
			i = i - 256;
	}
	return (i);
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
		if (rv)
			return (rv);
	}
	return (0);
}
