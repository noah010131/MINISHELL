/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:55:03 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/27 17:22:50 by chanypar         ###   ########.fr       */
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

int	exec(char *command, char **argv, t_cmds **ret, char *check)
{
	int	pid;
	int	status;


	(void)ret;
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
		status = check_exec(command, WEXITSTATUS(status), check);
		free(command);
		free(argv);
		return (status);
	}
	return (0);
}

int exec_command(t_cmds *c, t_cmds **ret)
{
	char	*command;
	char	**argv;
	int		i;	

	argv = NULL;
	command = ft_strjoin("/bin/", c->name);
	argv = malloc(100);
	if (!argv)
		return (-1);
	i = 0;
	while (c)
	{	
		if (c->code_id >= 11 & c->code_id <= 14)
		{
			c = c->next;
			if (ft_strcmp(c->name, (*(*ret)->file)->file_name) == 0)
				c = c->next;
		}
		argv[i++] = c->name;
		if (!c->next || (c->next->code_id != 9 && c->next->code_id != 21))
			break ;
		c = c->next;
	}
	argv[i] = NULL;
	return (exec(command, argv, ret, c->name));
}
