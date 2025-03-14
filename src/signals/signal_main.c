/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:15:34 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/14 12:31:24 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	clear_rl_line(void)
// {
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// }

// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	if (g_exit_code != -2) // sig == ctrl c
// 		clear_rl_line();
// 		// printf("\n%s", "MINI:");
// 	// else
// 	// 	printf("\n");
// 	g_exit_code = 130;
// }

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	clear_rl_line();
	if (g_exit_code == 0)
		rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
	exit(0);
}

int	signal_exit_check(int status, int	*flag)
{
	if (WTERMSIG(status) == SIGINT)
	{
		*flag = 1;
		status = 130;
	}
	if (WTERMSIG(status) == SIGQUIT)
	{
		*flag = 1;
		ft_putstr_fd("Quit (core dumped)\n", 2);
		status = 131;
	}
	return (status);
}

void	exec_ve(char *command, t_pars *c, char **env)
{
	signal(SIGQUIT, sigquit_handler);
	// signal(SIGTSTP, SIG_DFL);
	execve(command, c->arguments, env);
	exit(EXIT_FAILURE);
}
