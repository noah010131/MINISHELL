/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:25:44 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/13 13:42:53 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_finish(t_cmds *current, t_cmds **ret, t_envp **lst, t_file **file)
{
	int		i;
	t_file	*current_file;

	current = *(ret);
	i = builtins_checker(current);
	execute_command(i, current, lst, ret);
	current_file = (*file);
	while (current_file->fd)
	{
		if (current_file->f)
		{
			if (f_close2(current_file->fd, file, current_file->f) == -1)
				return (-1);
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
	int	copy_stdin_out[2];

	copy_stdin_out[0] = 0;
	copy_stdin_out[1] = 0;
	while (1)
	{
		if (current->code_id == 11)
			copy_stdin_out[0] = oper_redir_in(current, file, copy_stdin_out[0]);
		else if (current->code_id == 12)
			copy_stdin_out[1] = oper_redir_out(current, file, copy_stdin_out[1]);
		else if (current->code_id == 13)
			copy_stdin_out[0] = oper_heredoc_in(current, file, copy_stdin_out[0]);
		else if (current->code_id == 14)
			copy_stdin_out[1] = oper_redir_app(current, file, copy_stdin_out[1]);
		if (copy_stdin_out[0] == -1 || copy_stdin_out[1] == -1)
			return (-1);
		current = find_name(current->next, 'r');
		if (!current->name)
			break ;
	}
	if (exec_finish(current, ret, lst, file) == -1)
		return (-1);
	if (reset_stdin_out(copy_stdin_out) == -1)
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

	if (!current)
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
	if (!(ft_strcmp(current->name, list_butilins[i])))
		return (i);
	i = 0;
	if (!current->prev)
		return (-1);
	while (i < 7 && ft_strcmp(current->prev->name, list_butilins[i]))
		i++;
	if (!(ft_strcmp(current->prev->name, list_butilins[i])))
		return (i);
	return (-1);
}