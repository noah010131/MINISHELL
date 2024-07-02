/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/02 13:17:49 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_code = 0;

void	sigint_handler(int sig)
{
	char	*cwd;
	char	shell_prompt[100];

	(void)sig;
	if (g_exit_code != -2)
	{
		cwd = getcwd(NULL, 1024);
		snprintf(shell_prompt, sizeof(shell_prompt), "%s $ ", cwd);
		printf("\n%s", shell_prompt);
	}
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

void	set_param(int ac, char **av, t_status **status)
{
	(void)ac;
	(void)av;
	*status = malloc(sizeof(t_status));
	if (!*status)

		exit(-1);
	(*status)->isexit = 0;
	using_history();
	g_exit_code = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*ft_readline(void)
{
	char	*cpy;
	char	*cwd;
	char	shell_prompt[100];

	cwd = getcwd(NULL, 1024);
	if (!cwd)
		return (NULL);
	snprintf(shell_prompt, sizeof(shell_prompt), "%s $ ", cwd);
	cpy = NULL;
	cpy = readline(shell_prompt);
	while (cpy && !*cpy)
	{
		free(cpy);
		cpy = readline(shell_prompt);
	}
	free(cwd);
	if (!cpy)
	{
		rl_clear_history();
		free(cpy);
		exit(0);
	}
	history(cpy);
	return (cpy);
}

int	main(int ac, char **av, char **env)
{
	t_cmds		**ret;
	t_envp		**lst;
	t_status	*status;
	char		*string;

	set_param(ac, av, &status);
	while (1)
	{
		string = ft_readline();
		ret = split_token(string);
		if (!ret)
			ft_free_all(ret, lst, status, 1);
		code_attr(ret);
		lst = lst_env(env);
		expanding(ret, lst);
		ret = pptreatment(ret);
		(*ret)->status = status;
		g_exit_code = convert_code(pipe_main(ret, lst));
		ft_free_all(ret, lst, status, 0);
		check_exit_code(status, g_exit_code, string);
	}
	return (0);
}
