/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:25:44 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/14 16:48:10 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_finish(t_cmds **ret, t_envp **lst, t_file **file)
{
	t_file	*current_file;
	t_cmds	*current;

	current = *(ret);
	parsing_command(builtins_checker(current), current, lst, ret);
	current_file = *(file);
	while (current_file->fd)
	{
		if (current_file->f)
		{
			if (f_close2(current_file->fd, file, current_file->f) == -1)
				return (-1);
			if (!(ft_strcmp(current_file->file_name, TEMP)))
				remove(TEMP);
		}
		else
		{
			if (f_close(current_file->fd, file) == -1)
				return (-1);
		}
		if (!current_file->next)
			break ;
		current_file = current_file->next;
	}
	return (0);
}

int	reset_stdin_out(int copy_stdin_out[])
{
	if (copy_stdin_out[0])
	{
		if (dup2(copy_stdin_out[0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (copy_stdin_out[1])
	{
		if (dup2(copy_stdin_out[1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	parsing_redir(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	int	cpy_stdin_out[2];

	cpy_stdin_out[0] = 0;
	cpy_stdin_out[1] = 0;
	while (current->name)
	{
		if (current->code_id == 11)
			cpy_stdin_out[0] = oper_redir_in(current, file, cpy_stdin_out[0]);
		else if (current->code_id == 12)
			cpy_stdin_out[1] = oper_redir_out(current, file, cpy_stdin_out[1]);
		else if (current->code_id == 13)
			cpy_stdin_out[0] = oper_heredoc_in(current, file, cpy_stdin_out[0]);
		else if (current->code_id == 14)
			cpy_stdin_out[1] = oper_redir_app(current, file, cpy_stdin_out[1]);
		if (cpy_stdin_out[0] == -1 || cpy_stdin_out[1] == -1)
			return (-1);
		current = find_name(current->next, 'r');
	}
	free(current);
	if (exec_finish(ret, lst, file) == -1)
		return (-1);
	if (reset_stdin_out(cpy_stdin_out) == -1)
		return (-1);
	return (0);
}

t_cmds	*find_name(t_cmds *current, char name)
{
	t_cmds	*null;

	if (name == 'r')
	{
		while (current->next && (current->code_id != 10)
			&& (!(current->code_id >= 11 && current->code_id <= 14)))
			current = current->next;
	}
	else
	{
		while (current->next && current->code_id != 10)
			current = current->next;
	}
	if (!current->next)
	{
		null = malloc(sizeof(t_cmds));
		null->code_id = 0;
		null->name = NULL;
		null->next = NULL;
		null->prev = NULL;
		return (null);
	}
	return (current);
}

int	builtins_checker(t_cmds *current)
{
	char	list_butilins[7][7];
	int		i;

	if (!current || !current->name)
		return (-1);
	ft_strlcpy(list_butilins[0], "echo", 5);
	ft_strlcpy(list_butilins[1], "cd", 3);
	ft_strlcpy(list_butilins[2], "pwd", 4);
	ft_strlcpy(list_butilins[3], "export", 7);
	ft_strlcpy(list_butilins[4], "unset", 6);
	ft_strlcpy(list_butilins[5], "env", 4);
	ft_strlcpy(list_butilins[6], "exit", 5);
	i = 0;
	while (i < 7 && ft_strcmp(current->name, list_butilins[i]))
		i++;
	if (i != 7)
		return (i);
	i = 0;
	if (!current->prev)
		return (-1);
	while (i < 7 && ft_strcmp(current->prev->name, list_butilins[i]))
		i++;
	if (i != 7)
		return (i);
	return (-1);
}
