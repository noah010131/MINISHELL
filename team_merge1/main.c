/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:11:32 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 16:35:21 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		g_exit_code = 0;

bool	find_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\t' || c == '\v');
}

bool	prompt_only_space(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && find_space(prompt[i]))
		i++;
	if (prompt[i] == '\0')
		return (true);
	return (false);
}

void	restart_readline(t_data *data, char **prompt)
{
	if (data->token_list)
		free_token_list(&data->token_list);
	init_token_list(&data->token_list);
	if (prompt && *prompt)
	{
		add_history(*prompt);
		free(*prompt);
		*prompt = NULL;
	}
}

int	parsing(t_data *data, char *prompt)
{
	if (!data->token_list)
		init_token_list(&data->token_list);
	tokenizer(prompt, data);
	if (data->token_list->open_quote_flag == ERR)
		return (ERR);
	expand_env(data->token_list, data->env_list);
	if (data->env_list->flag == ERR)
		return (ERR);
	merge_token_str(data->token_list);
	remove_space_token(&data->token_list);
	return (syntax_check(data->token_list));
}

void	init_ori(t_ori *ori)
{
	ori->data = NULL;
	ori->envs = NULL;
	ori->parsee = NULL;
	ori->request = NULL;
	ori->env = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_ori	ori;

	init_all(&data, ac, av, envp);
	transfer_env(&data, &ori, envp);
	while (1)
	{
		data.prompt = ft_readline(&data);
		if (parsing(&data, data.prompt) == ERR)
		{
			if (data.env_list->flag == ERR)
				return (free_all(&data, &data.prompt), 0);
			restart_readline(&data, &data.prompt);
			continue ;
		}
		ori.parsee = change_struct(data.token_list);
		//parser_check_print(ori.parsee); // 이 부분에서 에러가 남 
		ori.data = &data;
		g_exit_code = pipe_main(ori.parsee, ori.envs, &ori);
		check_exit_code(ori.parsee, g_exit_code, ori.envs, &ori);
		synchro_env(&data, &ori);
		free_pars_list(ori.parsee);
		restart_readline(&data, &data.prompt);
	}
	return (free_all(&data, &data.prompt), 0);
}
