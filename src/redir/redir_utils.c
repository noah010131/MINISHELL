/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:34:48 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 00:49:56 by chanypar         ###   ########.fr       */
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
int	put_heredoc(FILE *temp, t_ori *ori, t_pipe *pipe, t_redir *save)
{
	char	*buffer;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			print_error
			("warning: heredoc delimited by end-of-file (wanted `end')\n");
			free_child(ori, 2, pipe, save);
			exit(fclose(temp));
		}
		buffer = expanding_hd(buffer, ori->envs);
		if (!((*ori->parsee)->redirections->filename) || !buffer||
			ft_strcmp(buffer, ((*ori->parsee)->redirections->filename)) == 0)
			break ;
		if (print_buff(buffer, fileno(temp)) == -1)
		{
			free_child(ori, 2, pipe, save);
			exit(-1);
		}
	}
	free_child(ori, 2, pipe, save);
	exit(fclose(temp));
}


int	read_heredoc(char *flag, t_ori *ori, t_pipe *pipe, t_redir *save)
{
	FILE	*temp;
	int		pid;
	int		status;

	if (access(TEMP, F_OK) == 0 && unlink(TEMP) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		temp = fopen(TEMP, flag);
		put_heredoc(temp, ori, pipe, save);
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

// TODO : fopen interdit
int	exec_heredoc(int flag, t_redir	*redirections)
{
	FILE	*temp;
	int		stdin_save;
	int		fd;

	temp = fopen(TEMP, "r");
	if (!temp)
		return (-1);
	redirections->f = temp;
	fd = fileno(temp);
	redirections->fd =fd;
	if (fd == -1)
		return (-1);
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
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
