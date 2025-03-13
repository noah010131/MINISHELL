/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:15:34 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/13 23:32:08 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_exit_code != -2)
		printf("\n%s", "MINI:");
	else
		printf("\n");
	g_exit_code = 130;
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
