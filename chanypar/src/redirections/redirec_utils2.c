/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:55:03 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/14 14:12:58 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* if CTRL + C, just appear new prompt*/

int	read_heredoc(char *end_str, t_file **file, int flag)
{
	FILE	*temp;
	int		fd;
	int		i;
	char	buffer[1024];

	i = ft_strlen(end_str);
	end_str[i] = '\n';
	if (flag)
		temp = f_open2(".temp_heredoc.txt", file, 14);
	else
	temp = f_open2(".temp_heredoc.txt", file, 12);
	if (!temp)
		return (-1);
	fd = fileno(temp);
	ft_strlcpy(buffer, "\0", 1);
	while (1)
	{
		printf("-> ");
		fgets(buffer, 1024, stdin);
		if (ft_strncmp(buffer, end_str, i + 1) == 0)
			break ;
		fprintf(temp, "%s", buffer);
	}
	if (f_close2(fd, file, temp) == -1)
		return (-1);
	return (0);
}

int	exec_heredoc(t_file **file, int flag)
{
	FILE	*temp;
	int		stdin_save;
	int		fd;

	temp = f_open2(".temp_heredoc.txt", file, 13);
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
int	exec(char *command, char **argv)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		execve(command, argv, NULL);
		return (-1);
	}
	wait(NULL);
	return (0);
}
int exec_command(t_cmds *cmds)
{
	char	*command;
	char	**argv;
	int		i;	

	argv = NULL;
	command = ft_strjoin("/bin/", cmds->name);
	argv = malloc(100);
	if (!argv)
		return (-1);
	i = 0;
	while (cmds && cmds->code_id == 9)
	{
		argv[i++] = cmds->name;
		if (!cmds->next || cmds->next->code_id != 9)
			break;
		cmds = cmds->next;
	}
	argv[i] = NULL;
	if (exec(command, argv) == -1)
		return (-1);
	return (0);
}

int	parsing_command(int i, t_cmds *cmds, t_envp **lst, t_cmds **ret)
{
	(void)ret;
	if (cmds->prev && cmds->code_id != 9)
		cmds = cmds->prev;
	if (cmds->prev && ft_strcmp(cmds->name, "cd") != 0 && ft_strcmp(cmds->name, "echo") != 0)
		cmds = cmds->prev;
	if (i == 0)
		ft_echo(cmds);
	if (i == 1)
		ft_cd(cmds, lst);
	if (i == 2)
		ft_pwd(cmds, lst);
	if (i == 3)
		ft_export(cmds, lst);
	if (i == 4)
		ft_unset(lst);
	// if (i == 5)
	// 	// env
	// if (i == 6)
	// 	// exit
	else
	{
		if (exec_command(cmds) == -1)
			return (-1);
	}
	return (0);
}
