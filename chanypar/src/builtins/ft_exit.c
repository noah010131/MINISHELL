/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:41:41 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/25 10:51:57 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_arg(t_cmds *current, t_status *status)
{
	int		i;
	char	num;

	i = 0;
	if (ft_isalpha(current->next->name[0]))
	{
		printf("exit: numeric argument required");
		status->code = 2;
		return (-1);
	}
	while (current->name[i] >= '0' && current->name[i] <= '9'
		|| (current->name[i] == '+' || current->name[i] == '-'))
		i++;
	if (!current->name[i])
	{
		i = ft_atoi(current->name);
		num = i;
		status->code = num;
	}
	return (0);
}

int	ft_exit(t_cmds **ret)
{
	t_cmds		*current;
	t_status	*status;
	int			i;

	current = *(ret);
	status = (*ret)->status;
	status->isexit = 1;
	if (current->next && !current->next->next)
	{
		if (check_arg(current, status))
			return (-1);
	}
	else if (current->next->next)
	{
		printf("exit: too many arguments");
		status->code = 1;
		return (-1);
	}
	else
		status->code = 0;
	return (0);
}
