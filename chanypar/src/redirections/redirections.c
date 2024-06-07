/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:49:28 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/07 14:21:23 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	operation_redir_in(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	int		fd;
	int		command;
	int		stdin_save;

	command = builtins_checker(current);
	if (command == -1)
		return (-1);
	if (!current->next && (current->next->code_id >= 10
			&& current->next->code_id <= 14))
		return (-1);
	stdin_save = dup(STDIN_FILENO);
	fd = f_open(current->next->name, file);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	if (f_close(fd, file) == -1)
		return (-1);
	execute_command(command, current->prev, lst);
	if (dup2(stdin_save, STDIN_FILENO) == -1)
		return (-1);
	retrun (0);
}

int	operation_redir_out(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	FILE	*f;
	int		fd;
	int		command;
	int		stdout_save;

	command = builtins_checker(current);
	if (command == -1 || (!current->next && (current->next->code_id >= 10
				&& current->next->code_id <= 14)))
		return (-1);
	stdout_save = dup(STDOUT_FILENO);
	f = f_open2(current->next->name, file, 12);
	if (!f)
		return (-1);
	fd = fileno(f);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	execute_command(command, current->prev, lst);
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
		return (-1);
	if (fclose(f) == -1)
		return (-1);
	return (0);
}

int	operation_heredoc_in(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	FILE	*f;
	int		fd;
	int		pid;
	int		command;
	int		stdin_save;

	command = builtins_checker(current);
	if (command == -1 || (!current->next && (current->next->code_id >= 10
				&& current->next->code_id <= 14)))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (read_heredoc(current->name, file) == -1)
			return (-1);
	}
	else if (pid > 0)
	{
		wait(NULL);
		if (exec_heredoc(file, command, current->prev, lst) == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	operation_redir_app(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	FILE	*f;
	int		fd;
	int		command;
	int		stdout_save;

	command = builtins_checker(current);
	if (command == -1 || (!current->next && (current->next->code_id >= 10
				&& current->next->code_id <= 14)))
		return (-1);
	stdout_save = dup(STDOUT_FILENO);
	f = f_open2(current->next->name, file, 14);
	if (!f)
		return (-1);
	fd = fileno(f);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	execute_command(command, current->prev, lst);
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
		return (-1);
	if (f_close2(fd, file, f) == -1)
		return (-1);
	retrun (0);
}

int	redirec_main(t_cmds **ret, t_file **file, t_envp **lst)
{
	t_cmds	*current;

	current = *(ret);
	current = find_name(current, 'r');
	if (!current)
		return (-1);
	if (current->code_id == 11) // "<"
		operation_redir_in(current, ret, lst, file);
	else if (current->code_id == 12) // ">"
		operation_redir_out(current, ret, lst, file);
	else if (current->code_id == 13) // "<<"
		operation_heredoc_in(current, ret, lst, file);
	else if (current->code_id == 14) // ">>"
		operation_redir_app(current, ret, lst, file);
	return (0);
}

