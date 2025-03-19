/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:34:48 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 01:04:39 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_buff(char *buffer, int filenum)
{
	if (filenum == -1)
		return (-1);
	ft_putstr_fd(buffer, filenum);
	ft_putchar_fd('\n', filenum);
	free(buffer);
	return (0);
}

int	put_heredoc(int fd, t_ori *ori, t_pipe *pipe, char name[])
{
	char	*buffer;

	(void)pipe;
	(void)ori;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			print_error
			("warning: heredoc delimited by end-of-file (wanted `end')\n");
			exit(close(fd));
		}
		if (!(name) || !buffer || ft_strcmp(buffer, (name)) == 0)
			break ;
		if (print_buff(buffer, fd) == -1)
		{
			exit(-1);
		}
	}
	exit(close(fd));
}

void	child_heredoc(int fd, t_ori *ori, t_pipe *pipe, t_redir *save)
{
	char	filename[1024];

	ft_strlcpy(filename, (*ori->parsee)->redirections->filename, 1024);
	free_child(ori, 2, pipe, save);
	put_heredoc(fd, ori, pipe, filename);
}

int	parent_waiting(int pid, int status)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (status == 2)
		write(1, "\n", 1);
	if (WTERMSIG(status) == SIGINT)
		status = 130;
	return (status);
}

int	read_heredoc(int flag, t_ori *ori, t_pipe *pipe, t_redir *save)
{
	int		pid;
	int		status;
	int		fd;

	status = 0;
	signal(SIGINT, SIG_DFL);
	if (access(TEMP, F_OK) == 0 && unlink(TEMP) != 0)
		return (-1);
	if (flag)
		fd = open(TEMP, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(TEMP, O_RDWR | O_CREAT | O_APPEND, 0644);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_heredoc(fd, ori, pipe, save);
	else
		return (parent_waiting(pid, status));
	return (0);
}
