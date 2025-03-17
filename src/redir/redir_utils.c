/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:34:48 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 10:42:03 by chanypar         ###   ########.fr       */
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
// TODO: fonction interdite : getchar
void clear_stdin_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// TODO: fonction interdite fclose
int	put_heredoc(int fd, t_ori *ori, t_pipe *pipe, t_redir *save)
{
	char	*buffer;

	(void)pipe;
	(void)save;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			print_error
			("warning: heredoc delimited by end-of-file (wanted `end')\n");
			free_child(ori, 2, pipe, save);
			exit(close(fd));
		}
		// buffer = expanding_hd(buffer, ori->envs);
		if (!((*ori->parsee)->redirections->filename) || !buffer||
			ft_strcmp(buffer, ((*ori->parsee)->redirections->filename)) == 0)
			break ;
		if (print_buff(buffer, fd) == -1)
		{
			free_child(ori, 2, pipe, save);
			exit(-1);
		}
	}
	free_child(ori, 2, pipe, save);
	exit(close(fd));
}


int	read_heredoc(int flag, t_ori *ori, t_pipe *pipe, t_redir *save)
{
	int		fd;
	int		pid;
	int		status;

	if (access(TEMP, F_OK) == 0 && unlink(TEMP) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (flag)
			fd = open(TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(TEMP, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// free_child(ori, 2, pipe, save);
		put_heredoc(fd, ori, pipe, save);
	}
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

void	expand_file(int fd, t_ori	*ori)
{
	char	*buff[1024];
	int		i;


	// (void)lst;
	// (void)fd;
	i = 0;
	fd = fileno((*ori->parsee)->redirections->f);
	buff[i] = get_next_line(fd);
	buff[i] = expanding_hd(buff[i], ori->envs);
	while (buff[i])
	{
		// free(buff);
		i++;
		buff[i] = get_next_line(fd);
		buff[i] = expanding_hd(buff[i], ori->envs);
	}
	i = -1;
	while (buff[++i])
	{
		printf("buff[%d] %s\n", i, buff[i]);
		print_buff(buff[i], fd);
	}
	// i = -1;
	// while (buff[++i])
	// 	free(buff[i]);
	// free(buff);
}
// TODO : fopen interdit
int	exec_heredoc(int flag, t_redir	*redirections)
{
	int		temp;
	int		stdin_save;

	if (TEMP)
		temp = open(TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!temp)
		return (-1);
	redirections->fd =temp;
	if (redirections->fd == -1)
		return (-1);
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(redirections->fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}

int	exec_heredoc1(int flag, t_redir	*redirections, t_ori *ori)
{
	int		temp;
	int		stdin_save;

	(void)ori;
	if (TEMP)
		temp = open(TEMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!temp)
		return (-1);
	redirections->fd =temp;
	if (redirections->fd == -1)
		return (-1);
	// expand_file(redirections->fd, ori);
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(redirections->fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}

int	execute_parsing(int std_s[], t_ori *ori, t_pipe *pipe, t_redir *save)
{
	if ((*ori->parsee)->redirections->type == REDIR_IN_S)
		std_s[0] = ch_err(oper_redir_in(*ori->parsee, std_s[0]), std_s);
	else if ((*ori->parsee)->redirections->type == REDIR_OUT_S)
		std_s[1] = ch_err(oper_redir_out(*ori->parsee, std_s[1]), std_s);
	else if ((*ori->parsee)->redirections->type == HEREDOC)
		std_s[0] = ch_err(oper_heredoc_in(std_s[0], ori, pipe, save), std_s);
	else if ((*ori->parsee)->redirections->type == REDIR_OUT_D)
		std_s[1] = ch_err(oper_redir_app(*ori->parsee, std_s[1]), std_s);
	if (std_s[0] < 0)
		return (std_s[0]);
	if (std_s[1] < 0)
		return (std_s[1]);
	return (0);
}
