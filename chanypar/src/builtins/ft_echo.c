/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/11 20:48:17 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmds *cmd)
{
	int flag;
	t_cmds *current;

	if (!cmd)
		return (1);
	cmd = cmd->next;
	if (cmd && ft_strcmp(cmd->name, "-n") == 0)
	{
		flag = 0;
		current = cmd->next;
	}
	else
		flag = 1;
	current = cmd;
	while (current && (current->code_id == 9
			|| (current->code_id >=20 && current->code_id != 22)))
	{
		printf("%s", current->name);
		current = current->next;
	}
	if (flag == 1)
		printf("\n");
	return (0);
}
