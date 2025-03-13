/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:33:42 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/13 12:18:35 by chanypar         ###   ########.fr       */
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
	i = -1;
	return (0);
}

int	open_heredoc(t_pars	*current, t_envp	**lst, FILE	*files[], int	c_stdout[])
{
	t_redir		*temp;
	int			i;

	temp = NULL;
	i = 0;
	while (current)
	{
		while (current && current->redirections
			&& current->redirections->type == HEREDOC)
		{
			c_stdout[0] =
				ch_err(oper_heredoc_in(current, c_stdout[0], lst), c_stdout);
			files[i++] = current->redirections->f;
			if (c_stdout[0] < 0)
				return (close_file(current->redirections), c_stdout[0] * -1);
			temp = current->redirections;
			current->redirections = current->redirections->next;
			free(temp->filename);
			free(temp);
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

int	pipe_helper(t_pars	**commands, t_envp	**lst)
{
	int			c_stdout[2];
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
	current = *commands;
	if (open_heredoc(current, lst, files, c_stdout) < 0)
		return (-1);
	else
	{
		if (reset_process(files, c_stdout) == -1)
			return (-1);
	}
	current = *commands;
	return (0);
}
