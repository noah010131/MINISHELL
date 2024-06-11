/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:49:28 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/11 17:03:48 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	oper_redir_in(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	int		fd;
	int		command;
	int		stdin_save;

	command = builtins_checker(current->prev);
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
	execute_command(command, current->prev, lst, ret);
	if (dup2(stdin_save, STDIN_FILENO) == -1)
		return (-1);
	return (0);
}

int	oper_redir_out(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	FILE	*f;
	int		fd;
	int		command;
	int		stdout_save;

	command = builtins_checker(current->prev);
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
	execute_command(command, current->prev, lst, ret);
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
		return (-1);
	if (fclose(f) == -1)
		return (-1);
	return (0);
}

int	oper_heredoc_in(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	int		pid;
	int		command;

	(void)ret;
	command = builtins_checker(current->prev);
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
		if (exec_heredoc(file, command, current->prev, lst, ret) == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	oper_redir_app(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	FILE	*f;
	int		fd;
	int		command;
	int		stdout_save;

	command = builtins_checker(current->prev);
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
	execute_command(command, current->prev, lst, ret);
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
		return (-1);
	if (f_close2(fd, file, f) == -1)
		return (-1);
	return (0);
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
	if (!current->next && !current->prev)
	{
		current = *(ret);
		i = builtins_checker(current);
		return (execute_command(i, current, lst, ret));
	}
	if (parsing_redir(current, ret, lst, file) == -1)
		return (-1);
	return (0);
}

