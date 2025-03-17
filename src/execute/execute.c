/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:56:02 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 22:10:06 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

// char	*put_path(char *command, t_envp **lst)
// {
// 	int		i;
// 	char	**temp_path;
// 	char	*path;

// 	i = 0;
// 	if (access(command, F_OK) == 0)
// 		return (ft_strdup(command));
// 	else
// 	{
// 		while (*lst)
// 		{
// 			if (ft_strcmp((*lst)->name, "PATH") == 0)
// 				break ;
// 			(*lst) = (*lst)->next;
// 		}
// 		if (!*lst)
// 			return (NULL);
// 		temp_path = ft_split((*lst)->value, ':');
// 		path = pathfinder(command, temp_path);
// 		i = -1;
// 		while (temp_path[++i])
// 			free(temp_path[i]);
// 		free(temp_path);
// 	}
// 	return (path);
// }

char	*put_path(char *command, t_envp **lst)
{
	int		i;
	char	**temp_path;
	char	*path;

	i = 0;
	while (*lst)
	{
		if (ft_strcmp((*lst)->name, "PATH") == 0)
			break ;
		(*lst) = (*lst)->next;
	}
	if (!*lst && access(command, F_OK) != 0)
		return (NULL);
	else if (!*lst && access(command, F_OK) == 0)
		return (ft_strdup(command));
	temp_path = ft_split((*lst)->value, ':');
	path = pathfinder(*&command, temp_path); // add *&command
	i = -1;
	while (temp_path[++i])
		free(temp_path[i]);
	free(temp_path);
	if (!path)
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
	}
	return (path);
}

int	exec_command(t_pars *c, t_envp **lst, char **env)
{
	char	*command;
	t_envp	*temp;

	temp = *lst;
	command = put_path(c->command, lst);
	*lst = temp;
	if (!command)
		return (check_error(command, c->arguments, 1));
	return (exec(command, c, env));
}

int	parsing_command(t_pars *c, t_envp **lst, t_ori *ori)
{
	if (c->command && ft_strcmp(c->command, "echo") == 0)
		return (g_exit_code = ft_echo(c));
	else if (c->command && ft_strcmp(c->command, "cd") == 0)
		return (g_exit_code = ft_cd(ori, c));
	else if (c->command && ft_strcmp(c->command, "pwd") == 0)
		return (g_exit_code = ft_pwd());
	else if (c->command && ft_strcmp(c->command, "export") == 0)
		return (g_exit_code = ft_export(c, lst));
	else if (c->command && ft_strcmp(c->command, "unset") == 0)
		return (g_exit_code = ft_unset(lst, c));
	else if (c->command && ft_strcmp(c->command, "env") == 0)
		return (g_exit_code = ft_env(lst));
	else if (c->command && ft_strcmp(c->command, "exit") == 0)
		return (g_exit_code = ft_exit(c));
	else if (c->command)
		return (g_exit_code = exec_command(c, lst, ori->env));
	else if (!c->command && c->arguments && !c->arguments[0])
	{
		print_no_command(c->command);
		return (127);
	}
	return (0);
}
