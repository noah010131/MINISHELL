/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/14 14:46:16 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_code = 0;

void	set_signal()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

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

void	parsing(t_data *data, char *prompt) // have to change return type to int for error
{
	if (!data->token_list)
		return ;
	tokenizer(prompt, data->token_list);
	expand_env(data->token_list, data->env_list);
	merge_token_str(data->token_list);
	// return (syntax_check(data->token_list)); have to implement syntax check
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_pars **parsee;
	char	*prompt;

	(void)parsee;
	prompt = NULL;
	init_data(&data, ac, av);
	env_parse(&data.env_list, env);
	set_signal();
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
		// if (parsing(&data, prompt))
		// {
		// 	// syntax error logic here
		// }
		parsee = parser(data.token_list);
		// g_exit_code = pipe_main(ori.parsee, ori.envs, &ori);
		// check_exit_code(ori.parsee, g_exit_code, ori.envs, &ori);
		restart_readline(&data, &prompt);

	}
	return (free_all(&data, &prompt), 0);
}
