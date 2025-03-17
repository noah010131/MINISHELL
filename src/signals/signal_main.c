/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:15:34 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 21:15:04 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	write(1, "\n", 1);
	clear_rl_line();
	// if (g_exit_code == 1)
	// 	write(1, "input : 1\n", 10);
	// else if (g_exit_code == -2)
	// 	write(1, "input : -2\n", 11);
	// else if (g_exit_code == 130)
	// 	write(1, "input : 130\n", 12);
	// else
	// 	printf("input : %d\n", g_exit_code);
	// fflush(stdout);
	rl_redisplay();
	g_exit_code = 130;
}

void	sigint_handler1(int sig)
{
	(void)sig;
	write(1, "okok\n", 5);
	// clear_rl_line();
	// // printf("input : %d\n", g_exit_code);
	// if (g_exit_code != -2)
	// 	rl_redisplay();
	// g_exit_code = 130;
	// // printf("output : %d\n", g_exit_code);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	// ft_putstr_fd("Quit (core dumped)\n", 2);
	// exit(0);
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
	signal(SIGINT, sigint_handler1);
	execve(command, c->arguments, env);
	exit(EXIT_FAILURE);
}
