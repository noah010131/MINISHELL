/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:41:41 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/25 11:57:14 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_arg(t_cmds *current, t_status *status)
{
	int		i;

	i = 0;
	if (ft_isalpha(current->next->name[0]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		status->code = 2;
		return (-1);
	}
	current = current->next;
	while (current->name[i] && ((current->name[i] >= '0' && current->name[i] <= '9')
		|| (current->name[0] == '+' || current->name[0] == '-')))
		i++;
	if (!current->name[i])
	{
		i = ft_atoi(current->name);
		if (i < 0)
			i = 256 + i;
		else if (i > 256)
			i = i - 256;
		status->code = i;
	}
	return (0);
}

int	ft_exit(t_cmds **ret)
{
	t_cmds		*current;
	t_status	*status;

	current = *(ret);
	status = (*ret)->status;
	status->isexit = 1;
	if (current->next && !current->next->next)
	{
		if (check_arg(current, status))
			return (-1);
	}
	else if (current->next && current->next->next)
	{
		ft_putstr_fd("exit: too many arguments", 2);
		status->code = 1;
		return (-1);
	}
	else
		status->code = 0;
	return (0);
}
