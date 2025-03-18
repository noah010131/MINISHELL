/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:43:11 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/18 10:34:34 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	oper_heredoc1(t_pars *c, int stdin_save, t_ori *ori, int files[])
{
	int		flag;

	flag = 1;
	if (stdin_save != 0)
	{
		if (dup2(stdin_save, STDIN_FILENO) == -1)
			return (-1);
		stdin_save = 0;
		flag = 0;
	}
	if (read_heredoc1(c->redirections->filename, flag, ori, files) == 130)
		return (130);
	return (exec_heredoc(stdin_save, c->redirections, ori));
}

int	close_file2(int files[])
{
	int		i;

	i = 0;
	while (files[i])
	{
		if (close(files[i]) == -1)
			return (-1);
		i++;
	}
	// if (access(TEMP, F_OK))
	// 	unlink(TEMP);
	return (0);
}

int	open_heredoc(t_ori *ori, int files[], int c_stdout[], t_pars *current)
{
	t_redir		*temp;
	t_pars		*save;
	int			i;

	temp = NULL;
	i = 0;
	save = current;
	while (save)
	{
		while (save && save->redirections
			&& save->redirections->type == HEREDOC)
		{
			c_stdout[0] = ch_err(oper_heredoc1
					(save, c_stdout[0], ori, files), c_stdout);
			files[i++] = save->redirections->fd;
			if (c_stdout[0] < 0)
				return (close_file(save->redirections), c_stdout[0] * -1);
			temp = save->redirections;
			save->redirections = save->redirections->next;
			free(temp->filename);
			free(temp);
		}
		save = save->next;
	}
	return (0);
}

int	reset_process(int files[], int c_stdout[])
{
	if (close_file2(files) == -1)
		return (reset_stdin_out(c_stdout), -1);
	if (reset_stdin_out(c_stdout) == -1)
		return (-1);	
	return (0);
}

int	pipe_helper(t_pars	**commands, t_ori *ori)
{
	int			c_stdout[2];
	int			num;
	t_pars		*current;
	int			files[100];

	c_stdout[0] = 0;
	c_stdout[1] = 0;
	current = *commands;
	ft_memset(files, 0, sizeof(files));
	while (current)
	{
		create_redir_in_order(current);
		current = (current)->next;
	}
	if (!count_pipes(commands))
		return (0);
	current = *commands;
	num = open_heredoc(ori, files, c_stdout, current);
	if (num)
		return (num * -1);
	if (reset_process(files, c_stdout) == -1)
		return (-1);
	current = *commands;
	return (0);
}
