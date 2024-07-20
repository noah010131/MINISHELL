/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:25:44 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/17 19:01:01 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_finish(t_cmds **ret, t_envp **lst, t_file **file, int flag)
{
	t_cmds	*current;
	int		rv;

	current = *(ret);
	rv = parsing_command(builtins_checker(current), current, lst, ret);
	if (!flag && rv == -1)
		return (1);
	if (close_file(file, 0) == -1)
	{
		free(file);
		return (1);
	}
	return (rv);
}

int	reset_stdin_out(int copy_stdin_out[])
{
	if (copy_stdin_out[0])
	{
		if (dup2(copy_stdin_out[0], STDIN_FILENO) == -1)
		{
			copy_stdin_out[0] = 0;
			return (-1);
		}
	}
	if (copy_stdin_out[1])
	{
		if (dup2(copy_stdin_out[1], STDOUT_FILENO) == -1)
		{
			copy_stdin_out[1] = 0;
			return (-1);
		}
	}
	return (0);
}

int	execute_parsing(t_cmds *current,
t_file **file, int cpy_stdin_out[], t_exptr *temp)
{
	t_status	*stat;
    t_cmds **ret;

    ret = temp->cmds;
    temp->num = cpy_stdin_out[0];
	stat = (*ret)->status;
	(*ret)->file = file;
	if (current->code_id == 11)
		cpy_stdin_out[0] = ch_err(oper_redir_in
				(current, file, cpy_stdin_out[0], stat), cpy_stdin_out);
	else if (current->code_id == 12)
		cpy_stdin_out[1]
			= ch_err(oper_redir_out
				(current, file, cpy_stdin_out[1], stat), cpy_stdin_out);
	else if (current->code_id == 13)
		cpy_stdin_out[0]
			= ch_err(oper_heredoc_in
				(current, file, temp, stat), cpy_stdin_out);
	else if (current->code_id == 14)
		cpy_stdin_out[1]
			= ch_err(oper_redir_app
				(current, file, cpy_stdin_out[1], stat), cpy_stdin_out);
	if (cpy_stdin_out[0] == -1 || cpy_stdin_out[1] == -1)
		return (-1);
	return (0);
}

int	parsing_redir(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	int	cpy_stdin_out[2];
	int	res;
	int	flag;
	int	rv;
    t_exptr temp;

	set_redir_parsing_param(cpy_stdin_out);
	res = 0;
	flag = 0;
    temp.cmds = ret;
    temp.env = lst;
	while (current && current->name)
	{
		if (execute_parsing(current, file, cpy_stdin_out, &temp) == -1)
			return (close_file(file, -1));
		current = find_name(current->next, 'r');
		if (res == -1)
			return (-1);
		flag = check_flag(flag, res);
	}
	free(current);
	rv = exec_finish(ret, lst, file, flag);
	if (reset_stdin_out(cpy_stdin_out) == -1)
		return (-1);
	return (rv);
}
