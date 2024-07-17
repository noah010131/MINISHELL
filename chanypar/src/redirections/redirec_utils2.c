/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:55:03 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/17 17:19:00 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec(char *command, char **argv, t_cmds **ret, char *check)
{
	int	pid;
	int	status;

	(void)ret;
	g_exit_code = -2;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		execve(command, argv, NULL);
		// exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		status = check_exec(command, WEXITSTATUS(status), check, status);
		free(command);
		free(argv);
		return (status);
	}
	return (0);
}
t_cmds	*check_redir_in_lst(t_cmds *c, t_cmds **ret)
{
	if (c->code_id >= 11 & c->code_id <= 14)
		{
			c = c->next;
			if (ft_strcmp(c->name, (*(*ret)->file)->file_name) == 0)
				c = c->next;
		}
	return (c);
}

int	exec_command(t_cmds *c, t_cmds **ret)
{
	char	**argv;
	char	*command;
	int		i;	

	argv = NULL;
	if (c->code_id == 0 || (c->code_id >= 11 && c->code_id <= 14))
		return (0);
	argv = malloc(100);
	if (!argv)
		return (-1);
	i = 0;
	command = put_path(c, ret);
	while (c)
	{
		c = check_redir_in_lst(c, ret);
		argv[i++] = c->name;
		if (!c->next || (c->next->code_id != 9 && c->next->code_id != 21))
			break ;
		c = c->next;
	}
	argv[i] = NULL;
	return (exec(command, argv, ret, c->name));
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

char	*put_path(t_cmds *c, t_cmds **ret)
{
	int		i;
	char	**temp_path;
	char	*path;

	i = 0;
	if (access(c->name, F_OK) == 0)
		return (ft_strdup(c->name));
	else
	{
		while ((*ret)->env[i])
		{
			if (ft_strncmp((*ret)->env[i], "PATH", 4) == 0)
				break ;
			i++;
		}
		if ((*ret)->env[i] == NULL)
			exit(1);
		temp_path = ft_split((*ret)->env[i], ':');
		path = pathfinder(c->name, temp_path);
		i = -1;
		while (temp_path[++i])
			free(temp_path[i]);
		free(temp_path);
	}
	return (path);
}
