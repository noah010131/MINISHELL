/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/26 14:09:06 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute(t_cmds *current, t_status *status, t_cmds **ret)
{
	while (current && (current->code_id == 9
			|| (current->code_id >=20 && current->code_id != 22) || (current->code_id >= 11 && current->code_id <= 14)))
	{
		if (current->code_id >= 11 && current->code_id <= 14)
		{
			current = current->next;
			if (ft_strcmp(current->name, (*(*ret)->file)->file_name) == 0)
				current = current->next;
			// if (current->next)
			// 	current = current->next;
			// else
			// 	return ;
		}
		if (!current)
			break;
		if (ft_strcmp(current->name, "$?") == 0)
			printf("%d", status->code);
		else
			printf("%s", current->name);
		current = current->next;
		if (current)
			printf(" ");
	}
}

int	ft_echo(t_cmds *cmd, t_cmds **ret)
{
	int 		flag;
	t_cmds		*current;
	t_status	*status;

	if (!cmd)
		return (1);
	current = cmd->next;
	status = (*ret)->status;
	if (cmd && ft_strcmp(cmd->name, "-n") == 0)
	{
		flag = 0;
		current = cmd->next;
	}
	else
		flag = 1;
	execute(current, status, ret);
	if (flag == 1)
		printf("\n");
	return (0);
}
