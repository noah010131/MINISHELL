/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:32:22 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/17 12:15:22 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_han(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n-> ", 4);
}

int	read_heredoc(char *end_str, t_file **file, int flag)
{
	FILE	*temp;
	int		i;
	char	buffer[1024];

	i = ft_strlen(end_str);
	end_str[i] = '\n';
	temp = f_open2(TEMP, file, flag);
	ft_strlcpy(buffer, "\0", 1);
	signal(SIGINT, sigint_han);
	while (1)
	{
		write(STDOUT_FILENO, "-> ", 3);
		if (fgets(buffer, 1024, stdin) == NULL)
		{
			ft_putchar_fd('\n', 1);
			f_close2(fileno(temp), file, temp);
			clearerr(stdin);
			return (-1);
		}
		if (ft_strncmp(buffer, end_str, i + 1) == 0)
			break ;
		fprintf(temp, "%s", buffer);
	}
	return (f_close2(fileno(temp), file, temp));
}

int	exec_heredoc(t_file **file, int flag)
{
	FILE	*temp;
	int		stdin_save;
	int		fd;

	temp = f_open2(TEMP, file, 13);
	if (!temp)
		return (-1);
	fd = fileno(temp);
	if (fd == -1)
		return (-1);
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	(*file)->f = temp;
	return (stdin_save);
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
