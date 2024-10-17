/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/10/17 14:29:20 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_code = 0;

void	sigint_handler(int sig)
{
	char	*cwd;

	(void)sig;
	if (g_exit_code != -2)
		printf("\n%s", "MINI:");
	else
		printf("\n");
}

void	history(char *str)
{
	HIST_ENTRY	**his_list;
	int			i;
	char		*cpy;

	i = -1;
	cpy = ft_strdup(str);
	his_list = NULL;
	add_history(cpy);
	free(cpy);
	his_list = NULL;
	his_list = history_list();
	if (ft_strcmp(str, "history") == 0)
	{
		while (his_list[++i])
			printf("%d: %s\n", i + 1, his_list[i]->line);
	}
}

void	set_param(int ac, char **av)
{
	(void)ac;
	(void)av;
	using_history();
	g_exit_code = 0;
}

char	*ft_readline(t_envp **lst)
{
	char	*cpy;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	cpy = NULL;
	cpy = readline("MINI:");
	while (cpy && !*cpy)
	{
		free(cpy);
		cpy = readline("MINI:");
	}
	if (!cpy)
	{
		free_envp(lst);
		free(lst);
		rl_clear_history();
		free(cpy);
		exit(0);
	}
	history(cpy);
	return (cpy);
}

void	init_ori(t_ori *ori)
{
	ori->cmds = NULL;
	ori->cmds = NULL;
	ori->parsee = NULL;
	ori->request = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_ori		ori;
	int			i;

	set_param(ac, av);
	init_ori(&ori);
	ori.envs = lst_env(env);
	while (1)
	{
		ori.request = ft_readline(ori.envs);
		if (all_toge(&ori))
			return (free_ori(&ori), 1);
		if (!ori.parsee)
			continue ;
		else
		{
			g_exit_code = convert_code(pipe_main(ori.parsee, ori.envs, &ori));
			check_exit_code(ori.parsee, g_exit_code, ori.envs, &ori);
		}
		free_tori(&ori);
	}
	return (0);
}
