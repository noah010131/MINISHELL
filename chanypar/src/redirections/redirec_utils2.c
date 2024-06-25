/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:55:03 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/25 10:58:08 by chanypar         ###   ########.fr       */
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
	temp = f_open2(TEMP, file, flag);
	if (!temp)
		return (-1);
	fd = fileno(temp);
	ft_strlcpy(buffer, "\0", 1);
	while (1)
	{
		// fprintf(STDOUT_FILENO, "%s", "-> "),
		write(STDOUT_FILENO, "-> ", 3);
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

int	exec(char *command, char **argv, t_cmds **ret)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		execve(command, argv, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		(*ret)->status->code = WEXITSTATUS(status);
		free(command);
		free(argv);
	}
	return (0);
}
int exec_command(t_cmds *cmds, t_cmds **ret)
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
			break ;
		cmds = cmds->next;
	}
	argv[i] = NULL;
	if (exec(command, argv, ret) == -1)
		return (-1);
	return (0);
}

int	parsing_command(int i, t_cmds *cmds, t_envp **lst, t_cmds **ret)
{
	t_status *status;

	status = (*ret)->status;
	if (cmds->prev && cmds->code_id != 9)
		cmds = cmds->prev;
	if (cmds->prev && ft_strcmp(cmds->name, "cd") != 0 && ft_strcmp(cmds->name, "echo") != 0)
		cmds = cmds->prev;
	if (i == 0)
		status->code = ft_echo(cmds, ret);
	else if (i == 1)
		status->code = ft_cd(cmds, lst);
	else if (i == 2)
		status->code = ft_pwd(cmds, lst);
	else if (i == 3)
		status->code = ft_export(cmds, lst);
	else if (i == 4)
		status->code = ft_unset(lst);
	else
	{
		if (exec_command(cmds, ret) == -1)
			return (-1);
	}
	return (0);
}

	// if (i == 5)
	// 	// env
	// if (i == 6)
	// 	// exit