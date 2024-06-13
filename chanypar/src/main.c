/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/13 11:33:48 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	char	*cwd;
	char	*usr;
	char	shell_prompt[100];

	cwd = getcwd(NULL, 1024);
	usr = getenv("USER");

	snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", usr, cwd);
	printf("\n%s", shell_prompt);
}

void	history(char *str)
{
	HIST_ENTRY	**his_list;
	int	i;

	i = -1;
	add_history(str);
	his_list = NULL;
	his_list = history_list();
	// int length = history_length;
	// for(int i = 0; i < length; i++)
	// 	his_list[i] = history_get(i + history_base);
	if (ft_strcmp(str, "history") == 0)
	{
		while (his_list[++i])
			printf("%d: %s\n", i + 1, his_list[i]->line);
	}
}

char	*join_string(char *str, t_cmds **ret, int flag)
{
	char	*temp;

	temp = NULL;
	if (flag)
	{
		temp = ft_strjoin(str, " ");
		free(str);
		str = ft_strdup(temp);
		free(temp);
	}
	temp = ft_strjoin(str, (*ret)->name);
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

int	print_terminal(t_cmds **ret)
{
	t_cmds	*current;
	char *str;
	int	i;
	int flag;
	int	len;

	i = 0;
	str = (char *)malloc(500);
	if (!str)
		return (-1);
	current = *ret;
	while(*ret)
	{
		len = ft_strlen((*ret)->name);
		if (!i)
			ft_strlcpy(str, (*ret)->name, len + 1);
		else
			str = join_string(str, ret, flag);
		flag = len;
		(*ret) = (*ret)->next;
		i++;
	}
	*ret = current;
	printf("%s\n", str);
	free(str);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_cmds **ret;
	// t_cmds *current;
	t_envp **lst;
	t_file **file;
	char	*cwd;
	char	*usr;
	char	shell_prompt[100];
	char	*cpy;

	(void)ac;
	(void)av;

	// (void)current;
	file =  malloc(sizeof(t_file));
	if (!file)
		return (-1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	using_history();
	cwd = getcwd(NULL, 1024);
	usr = getenv("USER");
	if (!cwd || !usr)
		return (-1);
	snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", usr, cwd);
	while (1)
	{
		cpy = readline(shell_prompt);
		if (!cpy || ft_strcmp(cpy, "exit") == 0)
		{
			free(cwd);
			free(cpy);
			break ;
		}
		while (!*cpy)
		{
			free(cpy);
			cpy = readline(shell_prompt);	
		}
		ret = split_token(cpy);
		history(cpy);
		free(cpy);
		code_attr(ret);
		if (!ret)
			return (printf("porblemooo\n"), 1);
		// current = *ret;
		// while (current)
		// {
		// 	printf("char :%s\n", current->name);
		// 	printf("code : %d\n_________\n", current->code_id);
		// 	current = current->next;
		// }
		lst = lst_env(env);
		expanding(ret, lst);
		ret = pptreatment(ret);
		// current = *ret;
		// while (current)
		// {	
		// 	printf("char :%s\n", current->name);
		// 	printf("code : %d\n_________\n", current->code_id);
		// 	current = current->next;
		// }
		free(cwd);
		pipe_main(ret, lst, file);
		// if (!check_builtins(ret, lst))
		// 	print_terminal(ret);
		cwd = getcwd(NULL, 1024); // au cas ou le cwd a change
		snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", usr, cwd);
		free_envp(lst);
		free_tcmd(ret);
	}
	return (0);
}
