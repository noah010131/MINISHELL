/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:25:44 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/25 13:30:14 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_finish(t_cmds **ret, t_envp **lst, t_file **file, int flag)
{
	t_cmds	*current;

	current = *(ret);
	if (!flag && parsing_command
		(builtins_checker(current), current, lst, ret) == -1)
		return (1);
	if (close_file(file) == -1)
		return (1);
	return (0);
}

int	reset_stdin_out(int copy_stdin_out[])
{
	if (copy_stdin_out[0])
	{
		if (dup2(copy_stdin_out[0], STDIN_FILENO) == -1)
			copy_stdin_out[1] = 0;
		return (1);
	}
	if (copy_stdin_out[1])
	{
		if (dup2(copy_stdin_out[1], STDOUT_FILENO) == -1)
			copy_stdin_out[1] = 0;
		return (1);
	}
	return (0);
}

int	check_in_out(t_cmds *current, t_envp **lst, t_cmds **ret, int stdin_out[])
{
	static int	prev_redir;
	t_cmds		*cur;

	if (!prev_redir)
	{
		prev_redir = current->code_id;
		return (0);
	}
	if (current->name && (!(prev_redir % 2) && (current->code_id % 2)))
	{
		cur = *(ret);
		if (parsing_command(builtins_checker(cur), cur, lst, ret) == -1)
			return (-1);
		reset_stdin_out(stdin_out);
		prev_redir = 0;
		return (1);
	}
	else
		prev_redir = current->code_id;
	return (0);
}

int	execute_parsing(t_cmds *current,
t_file **file, int cpy_stdin_out[], t_cmds **ret)
{
	t_status	*stat;

	stat = (*ret)->status;
	if (current->code_id == 11)
		cpy_stdin_out[0]
			= oper_redir_in(current, file, cpy_stdin_out[0], stat);
	else if (current->code_id == 12)
		cpy_stdin_out[1]
			= oper_redir_out(current, file, cpy_stdin_out[1], stat);
	else if (current->code_id == 13)
		cpy_stdin_out[0]
			= oper_heredoc_in(current, file, cpy_stdin_out[0], stat);
	else if (current->code_id == 14)
		cpy_stdin_out[1]
			= oper_redir_app(current, file, cpy_stdin_out[1], stat);
	if (cpy_stdin_out[0] == -1 || cpy_stdin_out[1] == -1)
		return (-1);
	return (0);
}

int	parsing_redir(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	int	cpy_stdin_out[2];
	int	res;
	int	flag;

	cpy_stdin_out[0] = 0;
	cpy_stdin_out[1] = 0;
	res = 0;
	flag = 0;
	while (current->name)
	{
		check_in_out(current, lst, ret, cpy_stdin_out);
		if (execute_parsing(current, file, cpy_stdin_out, ret) == -1)
			return (-1);
		current = find_name(current->next, 'r');
		res = check_in_out(current, lst, ret, cpy_stdin_out);
		if (res == -1)
			return (-1);
		if (!flag)
			flag = res;
	}
	free(current);
	if (exec_finish(ret, lst, file, flag) || reset_stdin_out(cpy_stdin_out))
		return (-1);
	return (0);
}
