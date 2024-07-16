/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:41:41 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/16 18:17:06 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_arg(t_cmds *current)
{
	int		i;

	i = 0;
	if (ft_isalpha(current->next->name[0]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	current = current->next;
	while (current->name[i]
		&& ((current->name[i] >= '0' && current->name[i] <= '9')
			|| (current->name[0] == '+' || current->name[0] == '-')))
		i++;
	if (!current->name[i])
	{
		i = ft_atoi(current->name);
		if (i < 0)
			i = 256 + i;
		else if (i > 256)
			i = i - 256;
	}
	return (i);
}

int	ft_exit(t_cmds **ret)
{
	t_cmds		*current;
	int			rv;

	current = *(ret);
	(*ret)->status->isexit = 1;
	rv = 0;
	if (current->next && !current->next->next)
	{
		rv = check_arg(current);
		if (rv)
			return (rv);
	}
	else if (current->next && current->next->next)
	{
		ft_putstr_fd("exit: too many arguments", 2);
		return (-1);
	}
	return (0);
}
