/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:56:02 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 06:01:13 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec(char *command, t_pars *c, char **env)
{
	int	pid;
	int	status;
	int	status_save;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		exec_ve(command, c, env);
	else
	{
		waitpid(pid, &status, 0);
		status_save = 0;
		status = signal_exit_check(status, &status_save);
		if (status_save)
		{
			free(command);
			return (status);
		}
		status = check_error(command, c->arguments, WEXITSTATUS(status));
		free(command);
		return (status);
	}
	return (0);
}

char	*pathfinder(char *cmd, char **path_t)
{
	int		i;
	char	*cmd_temp;
	char	*add_slash;

	if (!path_t)
		return (NULL);
	i = 0;
	add_slash = ft_strjoin("/", cmd);
	if (!add_slash)
		return (0);
	while (path_t[i])
	{
		cmd_temp = ft_strjoin(path_t[i], add_slash);
		if (!cmd_temp)
			return (free(add_slash), NULL);
		if (access(cmd_temp, F_OK) == 0)
			return (free(add_slash), cmd_temp);
		free(cmd_temp);
		i++;
	}
	free(add_slash);
	return (NULL);
}

char	*put_path(char *command, t_envp **lst)
{
	int		i;
	char	**temp_path;
	char	*path;

	while (*lst)
	{
		if (ft_strcmp((*lst)->name, "PATH") == 0)
			break ;
		(*lst) = (*lst)->next;
	}
	if (!*lst && access(command, X_OK) != 0)
		return (NULL);
	else if (!*lst && access(command, X_OK) == 0)
		return (ft_strdup(command));
	temp_path = ft_split((*lst)->value, ':');
	path = pathfinder(*&command, temp_path);
	i = -1;
	while (temp_path[++i])
		free(temp_path[i]);
	free(temp_path);
	if (!path)
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
	return (path);
}

int	slach_checker(char	*command)
{
	int	i;
	int	check;
	int	checker_s;

	i = 0;
	check = 0;
	checker_s = 0;
	if (!ft_strcmp("..", command) || !ft_strcmp(".", command))
		return (print_message(command, 4), 127);
	while (command[i] && (command[i] == '/' || command[i] == '.'))
	{
		if (command[i] == '/')
			checker_s = 1;
		check = 0;
		while (command[i + check] && command[i + check] == '.')
			check++;
		if (check >= 3)
			return (print_message(command, 4), 127);
		i++;
	}
	if (!command[i] && checker_s)
		return (print_message(command, 1), 126);
	return (0);
}

int	exec_command(t_pars *c, t_envp **lst, char **env)
{
	char	*command;
	t_envp	*temp;
	int		rv;

	temp = *lst;
	rv = slach_checker(c->command);
	if (rv)
		return (rv);
	command = put_path(c->command, lst);
	*lst = temp;
	if (!command)
		return (check_error(command, c->arguments, 1));
	return (exec(command, c, env));
}
