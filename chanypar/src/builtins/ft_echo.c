/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/31 16:35:01 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmds *cmd)
{
	int flag;
	t_cmds *current;

	if (!cmd)
		return (1);
	current = cmd;
	current = cmd->next;
	if (ft_strcmp(cmd->name, "-n") == 0)
	{
		flag = 1;
		current = current->next;
	}
	else
		flag = 0;
	while (current)
	{
		printf("%s\n", current->name);
		current = current->next;
	}
	if (flag == 1)
		printf("\n");
	return (0);
}