/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:53:15 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 16:53:16 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_token_list(&data->token_list);
	init_token_list(&data->token_list);
	if (prompt && *prompt)
	{
		add_history(*prompt);
		free(*prompt);
		*prompt = NULL;
	}
}

void	parsing(t_data *data, char *prompt)
{
	if (!data->token_list)
		return ;
	tokenizer(prompt, data->token_list);
	expand_env(data->token_list, data->env_list);
	merge_token_str(data->token_list);
	token_list_check_print(data->token_list);
}

int	main(int arc, char **argv, char **envp)
{
	t_data	data;
	char	*prompt;

	prompt = NULL;
	init_data(&data, arc, argv);
	env_parse(&data.env_list, envp);
	while (1)
	{
		prompt = readline("minishell$ ");
		if (!prompt)
		{
			ft_printf("exit\n");
			free_all(&data, &prompt);
			exit(0);
		}
		if (!*prompt || prompt_only_space(prompt))
		{
			free(prompt);
			prompt = NULL;
			continue ;
		}
		parsing(&data, prompt);
		restart_readline(&data, &prompt);
	}
	return (free_all(&data, &prompt), 0);
}
