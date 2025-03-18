/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/18 02:39:08 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_argument(char	*argument)
{
	int	i;

	i = 0;
	if (argument[i] != '-')
		return (0);
	if (!ft_strcmp(argument, "-n"))
		return (1);
	i++;
	while (argument[i] && argument[i] == 'n')
		i++;
	if (argument[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(t_pars *cmd)
{
	int		flag;
	int		i;

	if (!cmd)
		return (1);
	i = 1;
	if (cmd->arguments && cmd->arguments[1]
		&& check_argument(cmd->arguments[1]))
	{
		flag = 0;
		while (cmd->arguments[i] && check_argument(cmd->arguments[i]))
			i++;
	}
	else
		flag = 1;
	while (cmd && cmd->arguments && cmd->arguments[i])
	{
		ft_putstr_fd(cmd->arguments[i], 1);
		if (cmd->arguments[i] && cmd->arguments[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}
