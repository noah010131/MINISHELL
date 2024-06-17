/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:41:41 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/17 15:34:24 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_arg(t_cmds *current, t_error *error)
{
	int	i;
	int	num;

	i = 0;
	if (ft_isalpha(current->next->name[0]))
	{
		ft_strlcpy(error->error_m, "exit: numeric argument required", 100);
		error->code = 2;
		return ;
	}
	while (current->name[i] >= '0' && current->name[i] <= '9'
		|| (current->name[i] == '+' || current->name[i] == '-'))
		i++;
	if (!current->name[i])
	{
		i = ft_atoi(current->name);
		if (i < 0)
			num = 256 + i;
		else if (i > 256)
			num = i - 256;
		error->code = num;
	}
	return ;
}

int	ft_exit(t_cmds **ret)
{
	t_cmds	*current;
	t_error	*error;
	int		i;

	current = *(ret);
	error = (*ret)->error;
	if (current->next && !current->next->next)
		check_arg(current, error);
	else if (current->next->next)
	{
		ft_strlcpy(error->error_m, "exit: too many arguments", 100);
		error->code = 1;
	}
	else
		error->code = 0;
	return 
}
