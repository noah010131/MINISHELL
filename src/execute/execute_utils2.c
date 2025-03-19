/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:48:51 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 00:50:37 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parsing_command(t_pars *c, t_envp **lst, t_ori *ori)
{
	if (c->command && ft_strcmp(c->command, "echo") == 0)
		return (g_exit_code = ft_echo(c));
	else if (c->command && ft_strcmp(c->command, "cd") == 0)
		return (g_exit_code = ft_cd(ori, c));
	else if (c->command && ft_strcmp(c->command, "pwd") == 0)
		return (g_exit_code = ft_pwd());
	else if (c->command && ft_strcmp(c->command, "export") == 0)
		return (g_exit_code = ft_export(c, lst));
	else if (c->command && ft_strcmp(c->command, "unset") == 0)
		return (g_exit_code = ft_unset(lst, c));
	else if (c->command && ft_strcmp(c->command, "env") == 0)
		return (g_exit_code = ft_env(lst));
	else if (c->command && ft_strcmp(c->command, "exit") == 0)
		return (g_exit_code = ft_exit(c));
	else if (c->command)
		return (g_exit_code = exec_command(c, lst, ori->env));
	else if (!c->command && c->arguments && !c->arguments[0])
	{
		print_no_command(c->command);
		return (127);
	}
	return (0);
}
