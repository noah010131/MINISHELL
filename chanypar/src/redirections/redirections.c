/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:49:28 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/13 14:40:08 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	oper_redir_in(t_cmds *current, t_file **file, int stdin_save)
{
	int		fd;
	// int		command;

	// command = builtins_checker(current->prev);
	// if (command == -1)
	// 	return (-1);
	// if (!current->next && (current->next->code_id >= 10
	// 		&& current->next->code_id <= 14))
	// 	return (-1);
	if (!stdin_save)
		stdin_save = dup(STDIN_FILENO);
	fd = f_open(current->next->name, file);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}

int	oper_redir_out(t_cmds *current, t_file **file, int stdout_save)
{
	FILE	*f;
	int		fd;
	// int		command;

	// command = builtins_checker(current->prev);
	// if (command == -1 || (!current->next && (current->next->code_id >= 10
	// 			&& current->next->code_id <= 14)))
	// 	return (-1);
	if (!stdout_save)
		stdout_save = dup(STDOUT_FILENO);
	f = f_open2(current->next->name, file, 12);
	if (!f)
		return (-1);
	(*file)->f = f;
	fd = fileno(f);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	return (stdout_save);
}

int	oper_heredoc_in(t_cmds *current, t_file **file, int stdin_save)
{
	int		pid;
	// int		command;

	// command = builtins_checker(current->prev);
	// if (command == -1 || (!current->next && (current->next->code_id >= 10
	// 			&& current->next->code_id <= 14)))
	// 	return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (read_heredoc(current->name, file) == -1)
			return (-1);
	}
	else if (pid > 0)
	{
		wait(NULL);
		stdin_save = exec_heredoc(file, stdin_save);
	}
	else
		return (-1);
	return (stdin_save);
}

int	oper_redir_app(t_cmds *current, t_file **file, int stdout_save)
{
	FILE	*f;
	int		fd;
	// int		command;

	// command = builtins_checker(current->prev);
	// if (command == -1 || (!current->next && (current->next->code_id >= 10
	// 			&& current->next->code_id <= 14)))
	// 	return (-1);
	if (!stdout_save)
		stdout_save = dup(STDOUT_FILENO);
	f = f_open2(current->next->name, file, 14);
	if (!f)
		return (-1);
	fd = fileno(f);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	return (stdout_save);
}

int	redirec_main(t_pipe *pipe)
{
	t_cmds	*current;
	t_cmds **ret;
	t_file **file;
	t_envp **lst;
	int	i;

	current = pipe->current;
	ret = pipe->ret;
	file = pipe->file;
	lst = pipe->lst;
	current = find_name(current, 'r');
	if (!current->next && !current->prev) // si y a pas de redirec
	{
		current = *(ret);
		i = builtins_checker(current);
		return (execute_command(i, current, lst, ret));
	}
	i = 0;
	if (parsing_redir(current, ret, lst, file) == -1)
		return (-1);
	return (0);
}

