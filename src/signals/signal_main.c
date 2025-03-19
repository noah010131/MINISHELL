/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:15:34 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 11:03:28 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	clear_rl_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	sigquit_handler(int sig)
{
	(void)sig;
}

int	signal_exit_check(int status, int	*flag)
{
	if (WTERMSIG(status) == SIGINT)
	{
		*flag = 1;
		write(1, "\n", 1);
		status = 130;
	}
	if (WTERMSIG(status) == SIGQUIT)
	{
		*flag = 1;
		write(1, "Quit (core dumped)\n", 19);
		status = 131;
	}
	return (status);
}

void	exec_ve(char *command, t_pars *c, char **env)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, SIG_DFL);
	execve(command, c->arguments, env);
	exit(EXIT_FAILURE);
}
