/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:36:27 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/12 01:01:55 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_error_code(char *name)
{
	int	status;

	status = -1;
	ft_putstr_fd("minishell: ", 2);
	if (errno == ENOENT)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		status = -127;
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("Permission denied: ", 2);
		status = -126;
	}
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
	return (status);
}

int	oper_redir_in(t_pars *c, int stdin_save)
{
	if (!stdin_save)
		stdin_save = dup(STDIN_FILENO);
	c->redirections->fd = open(c->redirections->filename, O_RDONLY);
	if (c->redirections->fd == -1)
		return (check_error_code(c->redirections->filename));
	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	if (errno == ENOENT)
	// 		ft_putstr_fd("no such file or directory: ", 2);
	// 	else if (errno == EACCES)
	// 		ft_putstr_fd("Permission denied: ", 2);
	// 	ft_putstr_fd(c->redirections->filename, 2);
	// 	ft_putstr_fd("\n", 2);
	// 	return (-1);
	// }
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
		return (check_error_code(c->redirections->filename));

	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	if (errno == ENOENT)
	// 		ft_putstr_fd("no such file or directory: ", 2);
	// 	else if (errno == EACCES)
	// 		ft_putstr_fd("Permission denied: ", 2);
	// 	ft_putstr_fd(c->redirections->filename, 2);
	// 	ft_putstr_fd("\n", 2);
	// 	return (-1);
	// }
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
	if (read_heredoc(c->redirections->filename, flag, lst) == -1)
		return (-1);
	return (exec_heredoc(stdin_save, c->redirections));
}

int	oper_redir_app(t_pars *c, int stdout_save)
{
	(void)stat;
	if (!stdout_save)
		stdout_save = dup(STDOUT_FILENO);
	c->redirections->f = fopen(c->redirections->filename, "a");
	if (!c->redirections->f)
				return (check_error_code(c->redirections->filename));

	
	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	if (errno == ENOENT)
	// 		ft_putstr_fd("no such file or directory: ", 2);
	// 	else if (errno == EACCES)
	// 		ft_putstr_fd("Permission denied: ", 2);
	// 	ft_putstr_fd(c->redirections->filename, 2);
	// 	ft_putstr_fd("\n", 2);
	// 	return (-1);
	// }
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
		if (return_value  < 0)
			return (close_file(command->redirections), return_value * -1);
		command->redirections = command->redirections->next;
	}
	return_value = parsing_command(command, lst, ori);
	command->redirections = save;
	if (close_file(command->redirections) == -1)
		return (reset_stdin_out(cpy_stdin_out), -1);
	if (reset_stdin_out(cpy_stdin_out) == -1)
		return (-1);
	return (return_value);
}
