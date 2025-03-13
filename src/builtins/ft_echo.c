/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/13 19:06:12 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_pars *cmd)
{
	int		flag;
	int		i;

	if (!cmd)
		return (1);
	i = 1;
	if (cmd->arguments && cmd->arguments[1]
		&& !ft_strcmp(cmd->arguments[1], "-n"))
	{
		flag = 0;
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
