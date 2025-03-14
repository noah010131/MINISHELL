/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:36:27 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/14 10:49:01 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	oper_redir_in(t_pars *c, int stdin_save)
{
	if (!stdin_save)
		stdin_save = dup(STDIN_FILENO);
	c->redirections->fd = open(c->redirections->filename, O_RDONLY);
	if (c->redirections->fd == -1)
		return (check_error_code(c->redirections->filename), -1);
	if (dup2(c->redirections->fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}

int	oper_redir_out(t_pars *c, int stdout_save)
{
	if (!stdout_save)
		stdout_save = dup(STDOUT_FILENO);
	c->redirections->f = fopen(c->redirections->filename, "wr");
	if (!c->redirections->f)
		return (check_error_code(c->redirections->filename), -1);
	c->redirections->fd = fileno(c->redirections->f);
	if (c->redirections->fd == -1)
		return (-1);
	if (dup2(c->redirections->fd, STDOUT_FILENO) == -1)
		return (-1);
	return (stdout_save);
}

int	oper_heredoc_in(t_pars *c, int stdin_save, t_envp **lst)
{
	char	*flag;

	flag = "wr";
	if (stdin_save != 0)
	{
		if (dup2(stdin_save, STDIN_FILENO) == -1)
			return (-1);
		stdin_save = 0;
		flag = "a";
	}
	if (read_heredoc(c->redirections->filename, flag, lst) == 130)
		return (130);
	return (exec_heredoc(stdin_save, c->redirections));
}

int	oper_redir_app(t_pars *c, int stdout_save)
{
	if (!stdout_save)
		stdout_save = dup(STDOUT_FILENO);
	c->redirections->f = fopen(c->redirections->filename, "a");
	if (!c->redirections->f)
		return (check_error_code(c->redirections->filename), -1);
	c->redirections->fd = fileno(c->redirections->f);
	if (c->redirections->fd == -1)
		return (-1);
	if (dup2(c->redirections->fd, STDOUT_FILENO) == -1)
		return (-1);
	return (stdout_save);
}

int	redirec_main(t_pars	*command, t_envp **lst, t_ori *ori)
{
	int			return_value;
	int			cpy_stdin_out[2];
	t_redir		*save;

	save = command->redirections;
	if (!command->redirections)
		return (parsing_command(command, lst, ori));
	cpy_stdin_out[0] = 0;
	cpy_stdin_out[1] = 0;
	while (command && command->redirections)
	{
		return_value = execute_parsing(command, cpy_stdin_out, lst);
		if (return_value < 0)
			return (close_file(command->redirections), return_value * -1);
		command->redirections = command->redirections->next;
	}
	command->redirections = save;
	return_value = parsing_command(command, lst, ori);
	if (close_file(command->redirections) == -1)
		return (reset_stdin_out(cpy_stdin_out), -1);
	if (reset_stdin_out(cpy_stdin_out) == -1)
		return (-1);
	return (return_value);
}
