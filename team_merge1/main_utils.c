/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:20:00 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 11:05:24 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	check_exit_code(t_pars **commands,
		int exit_code, t_envp **lst, t_ori *ori)
{
	int	is_exit;

	(void)ori;
	unlink(TEMP);
	unlink(OUTPUT);
	if (!*commands || !(*commands)->command)
		return ;
	is_exit = ft_strcmp((*commands)->command, "exit");
	if (exit_code == 0 && is_exit)
		return ;
	if (!is_exit)
	{
		free_envp(lst);
		free(lst);
		free_all(ori->data, &ori->data->prompt);
		free_pars_list(ori->parsee);
		exit(exit_code);
	}
}

char	*ft_readline(t_data *data)
{
	char	*prompt;

	prompt = NULL;
	signal(SIGINT, sigint_handler);
	prompt = readline("minishell$ ");
	if (!prompt)
	{
		ft_printf("exit\n");
		free_all(data, &prompt);
		exit(0);
	}
	if (!*prompt || prompt_only_space(prompt))
	{
		free(prompt);
		prompt = NULL;
		while (prompt && !*prompt)
			prompt = readline("minishell$ ");
	}
	add_history(prompt);
	signal(SIGINT, SIG_IGN);
	return (prompt);
}

void	init_all(t_data *data, int ac, char **av, char **envp)
{
	init_data(data, ac, av);
	env_parse(&data->env_list, envp);
	set_signal();
}

void	free_pars_ls(t_pars **parsee)
{
	t_pars	*current_p;
	t_pars	*cache_p;
	t_redir	*current_r;
	t_redir	*cache_r;

	if (!parsee)
		return ;
	current_p = *parsee;
	while (current_p)
	{
		current_r = current_p->redirections;
		cache_p = current_p->next;
		freee_error(current_p->arguments);
		free(current_p);
		while (current_r)
		{
			cache_r = current_r->next;
			free(current_r->filename);
			free(current_r);
			current_r = cache_r;
		}
		current_p = cache_p;
	}
	free(parsee);
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
