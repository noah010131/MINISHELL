/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:48:51 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 04:29:42 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	oper_heredoc_in(int stdin_save, t_ori *ori, t_pipe *pipe, t_redir *save)
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
	if (read_heredoc(flag, ori, pipe, save) == 130)
		return (130);
	return (exec_heredoc(stdin_save, (*ori->parsee)->redirections, ori));
}

int	oper_redir_app(t_pars *c, int stdout_save)
{
	if (!stdout_save)
		stdout_save = dup(STDOUT_FILENO);
	if (!c->redirections->filename)
		return (check_error_code(c->redirections->filename), -1);
	c->redirections->fd
		= open(c->redirections->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (c->redirections->fd == -1)
		return (check_error_code(c->redirections->filename), -1);
	if (c->redirections->fd == -1)
		return (-1);
	if (dup2(c->redirections->fd, STDOUT_FILENO) == -1)
		return (-1);
	return (stdout_save);
}
