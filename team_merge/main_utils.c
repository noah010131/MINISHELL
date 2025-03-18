/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:20:00 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/18 02:03:46 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	check_exit_code(t_pars **commands, int exit_code, t_envp **lst, t_ori *ori)
{
	int	is_exit;

	(void)ori;
	if (!*commands || !(*commands)->command)
		return ;
	is_exit = ft_strcmp((*commands)->command, "exit");
	if (exit_code == 0 && is_exit)
		return ;
	if (!is_exit)
	{
		free(lst);
		exit(exit_code);
	}
}

char	*ft_readline(t_data *data)
{
	char	*prompt;

	prompt = NULL;
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
	return (prompt);
}

void	init_all(t_data *data, int ac, char **av, char **envp)
{
	init_data(data, ac, av);
	env_parse(&data->env_list, envp);
	set_signal();
}
