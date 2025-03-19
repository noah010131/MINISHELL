/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:36:27 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 04:29:51 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	init_stdin_out(int cpy_stdin_out[2])
{
	cpy_stdin_out[0] = 0;
	cpy_stdin_out[1] = 0;
}

int	redirec_submain(t_pars	*command, t_ori *ori, t_pipe *pipe, t_redir *save)
{
	int	return_value;
	int	cpy_stdin_out[2];
	int	free_flag;

	free_flag = pipe->num_pipes;
	init_stdin_out(cpy_stdin_out);
	while (command && command->redirections)
	{
		return_value = execute_parsing(cpy_stdin_out, ori, pipe, save);
		if (return_value < 0)
		{
			if (!free_flag)
				(*ori->parsee)->redirections = save;
			return (close_file(command->redirections),
				free_child(ori, free_flag, pipe, save), return_value * -1);
		}
		command->redirections = command->redirections->next;
	}
	command->redirections = save;
	return_value = parsing_command(command, ori->envs, ori);
	if (close_file(command->redirections) == -1)
		return (reset_stdin_out(cpy_stdin_out), -1);
	if (reset_stdin_out(cpy_stdin_out) == -1)
		return (free_child(ori, free_flag, pipe, save), -1);
	return (free_child(ori, free_flag, pipe, save), return_value);
}

int	redirec_main(t_pars	*command, t_envp **lst, t_ori *ori, t_pipe *pipe)
{
	int			return_value;
	int			free_flag;
	t_redir		*save;

	free_flag = pipe->num_pipes;
	save = NULL;
	if (!command->redirections)
	{
		return_value = parsing_command(command, lst, ori);
		return (free_child(ori, free_flag, pipe, save), return_value);
	}
	save = command->redirections;
	return (redirec_submain(command, ori, pipe, save));
}
