/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:33:42 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 01:07:08 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	remove_heredoc(t_pars	**commands)
// {
// 	t_pars	*current;
// 	t_redir	*temp;

// 	current = *commands;
// 	temp = NULL;
// 	while (current)
// 	{
// 		while (current->redirections && current->redirections->type == HEREDOC)
// 		{
// 			temp = current->redirections;
// 			current->redirections = current->redirections->next;
// 			free(temp);
// 		}
// 		current = current->next;
// 	}
// }
int	put_heredoc1(char *end_str, FILE *temp, t_ori *ori, t_pipe *pipe)
{
	char	*buffer;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			print_error
			("MINI: warning: heredoc delimited by end-of-file (wanted `end')\n");
			free_child1(ori->envs, ori, 1, pipe);
			exit(fclose(temp));
		}
		buffer = expanding_hd(buffer, ori->envs);
		if (!end_str || !buffer || ft_strcmp(buffer, end_str) == 0)
			break ;
		if (print_buff(buffer, fileno(temp)) == -1)
		{
			free_child1(ori->envs, ori, 1, pipe);
			exit(-1);
		}
	}
	free_child1(ori->envs, ori, 1, pipe);
	exit(fclose(temp));
}

int	read_heredoc1(char *end_str, char *flag, t_ori *ori, t_pipe *pipe)
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
		put_heredoc1(end_str, temp, ori, pipe);
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
int	oper_heredoc_in1(t_pars *c, int stdin_save, t_ori *ori, t_pipe *pipe)
{
	char	*flag;

	flag = "wr";
	if (stdin_save != 0)
	{
		if (dup2(stdin_save, STDIN_FILENO) == -1)
			return (-1);
		stdin_save = 0;
		flag = "a";
	}
	if (read_heredoc1(c->redirections->filename, flag, ori, pipe) == 130)
		return (130);
	return (exec_heredoc(stdin_save, c->redirections));
}

int	close_file2(FILE	*files[])
{
	int		i;

	i = 0;
	while (files[i])
	{
		if (fclose(files[i]) == -1)
			return (-1);
		i++;
	}
	if (access(TEMP, F_OK))
		unlink(TEMP);
	return (0);
}

int	open_heredoc(t_ori *ori, FILE	*files[], int	c_stdout[], t_pipe *pipe)
{
	// t_redir		*temp;
	t_pars		*current;
	int			i;

	// temp = NULL;
	i = 0;
	current = *ori->parsee;
	while (current)
	{
		while (current && current->redirections
			&& current->redirections->type == HEREDOC)
		{
			c_stdout[0] =
				ch_err(oper_heredoc_in1(current, c_stdout[0], ori, pipe), c_stdout);
			files[i++] = current->redirections->f;
			if (c_stdout[0] < 0)
				return (close_file(current->redirections), c_stdout[0] * -1);
			// temp = current->redirections;
			current->redirections = current->redirections->next;
			// free(temp->filename);
			// free(temp);
		}
		current = current->next;
	}
	return (0);
}

int	reset_process(FILE	*files[], int	c_stdout[])
{
	if (close_file2(files) == -1)
		return (reset_stdin_out(c_stdout), -1);
	if (reset_stdin_out(c_stdout) == -1)
		return (-1);	
	return (0);
}

int	pipe_helper(t_pars	**commands, t_ori *ori, t_pipe *pipe)
{
	int			c_stdout[2];
	int			num;
	t_pars		*current;
	FILE		*files[100];

	c_stdout[0] = 0;
	c_stdout[1] = 0;
	current = *commands;
	ft_memset(files, 0, sizeof(files));
	while (current)
	{
		create_redir_in_order(current);
		current = (current)->next;
	}
	if (!count_pipes(commands))
		return (0);
	current = *commands;
	num = open_heredoc(ori, files, c_stdout, pipe);
	if (num)
		return (num * -1);
	else
	{
		if (reset_process(files, c_stdout) == -1)
			return (-1);
	}
	current = *commands;
	return (0);
}
