/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:49:28 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/25 10:53:17 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	oper_redir_in(t_cmds *current,
	t_file **file, int stdin_save, t_status *stat)
{
	int		fd;

	(void)stat;
	if (!stdin_save)
		stdin_save = dup(STDIN_FILENO);
	fd = f_open(current->next->name, file);
	if (fd == -1)
	{
		printf("no such file or directory: %s\n", current->next->name);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}

int	oper_redir_out(t_cmds *current,
	t_file **file, int stdout_save, t_status *stat)
{
	FILE	*f;
	int		fd;

	(void)stat;
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

int	oper_heredoc_in(t_cmds *current,
	t_file **file, int stdin_save, t_status *stat)
{
	int	flag;

	flag = 12;
	(void)stat;
	if (stdin_save != 0)
	{
		if (dup2(stdin_save, STDIN_FILENO) == -1)
			return (-1);
		stdin_save = 0;
		flag = 14;
	}

	if (read_heredoc(current->next->name, file, flag) == -1)
		return (-1);
	stdin_save = exec_heredoc(file, stdin_save);
	return (stdin_save);
}

int	oper_redir_app(t_cmds *current,
	t_file **file, int stdout_save, t_status *stat)
{
	FILE	*f;
	int		fd;

	(void)stat;
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
	t_cmds	**ret;
	t_file	**file;
	t_envp	**lst;
	int		i;

	current = pipe->current;
	ret = pipe->ret;
	file = pipe->file;
	lst = pipe->lst;
	current = *(ret);
	current = find_name(current, 'r');
	if (!current->name)
	{
		free(current);
		current = *(ret);
		i = builtins_checker(current);
		return (parsing_command(i, current, lst, ret));
	}
	i = 0;
	if (parsing_redir(current, ret, lst, file) == -1)
		return (-1);
	return (0);
}

