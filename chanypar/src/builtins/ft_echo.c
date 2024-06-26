/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/26 19:04:29 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int 	check_file_name(char *name, t_cmds **ret)
{
	t_file	*file;

	file = (*(*ret)->file);
	ft_putstr_fd(file->file_name, 2);
	while (file)
	{
		if (ft_strcmp(name, file->file_name) == 0)
			return (1);
		file = file->prev;
	}
	return (0);
}

void	execute(t_cmds *current, t_status *status, t_cmds **ret)
{
	while (current && (current->code_id == 9
			|| (current->code_id >=20 && current->code_id != 22)
			|| current->code_id == 11))
	{
		while (current && (current->code_id == 11))
		{
			current = current->next;
			if (check_file_name(current->name, ret))
				current = current->next;
		}
		if (!current)
			break ;
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
	int			flag;
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
