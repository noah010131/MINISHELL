/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:33:42 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 15:26:21 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	put_heredoc1(char end_str[], int fd, t_ori *ori, int files[])
{
	char	*buffer;

	(void)ori;
	(void)files;
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
		if (!end_str || !buffer || ft_strcmp(buffer, end_str) == 0)
			break ;
		if (print_buff(buffer, fd) == -1)
			exit(-1);
	}
	exit(close(fd));
}

void	child_heredoc1(char *end_str, int flag, t_ori *ori, int files[])
{
	int		fd;
	char	filename[1024];

	if (flag)
		fd = open(TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(TEMP, O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_strlcpy(filename, end_str, 1024);
	free_child1(ori->envs, ori, 1, files);
	put_heredoc1(filename, fd, ori, files);
}

int	read_heredoc1(char *end_str, int flag, t_ori *ori, int files[])
{
	int		pid;
	int		status;

	if (access(TEMP, F_OK) == 0 && unlink(TEMP) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_heredoc1(end_str, flag, ori, files);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (status == 2)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGINT)
			status = 130;
		return (status);
	}
	return (0);
}

t_pars	*put_command(t_pars	**c, int i)
{
	int		num;
	t_pars	*tmp;
	t_pars	*current;

	num = 0;
	current = (*c);
	while (current && num < i)
	{
		if (current->next)
			tmp = current->next;
		current = tmp;
		num++;
	}
	if (!current)
		write(2, "NULL\n", 5);
	return (current);
}

void	free_fds(int **fds, int end)
{
	int	i;

	i = -1;
	while (i <= end)
		free(fds[i]);
	free(fds);
}