/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:33:42 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/13 08:23:50 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_heredoc(t_pars	**commands)
{
	t_pars	*current;
	t_redir	*temp;

	current = *commands;
	temp = NULL;
	while (current)
	{
		while (current->redirections && current->redirections->type == HEREDOC)
		{
			temp = current->redirections;
			current->redirections = current->redirections->next;
			free(temp);
		}
		current = current->next;
	}
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
	i = -1;
	return (0);
}

int	pipe_helper(t_pars	**commands, t_envp	**lst, t_pipe	*pipe, t_ori *ori)
{
	int			c_stdout[2];
	// int			return_value;
	t_pars		*current;
	// t_redir		*save;
	FILE		*files[100];
	int			i;

	c_stdout[0] = 0;
	c_stdout[1] = 0;
	(void)pipe;
	(void)lst;
	(void)ori;
	// (void)commands;
	// step 1
	i = 0;
	// current = *commands;
	ft_memset(files, 0, sizeof(files));
	// while (current)
	// {
	// 	create_redir_in_order(current);
	// 	current = (current)->next;
	// }
	// current = *commands;
	// step 2
	// while (current)
	// {
	// 	while (current && current->redirections && current->redirections->type == HEREDOC)
	// 	{
	// 		c_stdout[0] = ch_err(oper_heredoc_in(current, c_stdout[0], lst), c_stdout);
	// 		files[i++] = current->redirections->f;
	// 		if (c_stdout[0] < 0)
	// 			return (close_file(current->redirections), c_stdout[0] * -1);
	// 		current->redirections = current->redirections->next;
	// 	}
	// 	current = current->next;
	// }
	// return_value = parsing_command(current, lst, ori);
	// current = *commands;
	// if (i)
	// {
	// 	if (close_file2(files) == -1) // there is a pipe between heredoc
	// 		return (reset_stdin_out(c_stdout), -1);
	// 	if (reset_stdin_out(c_stdout) == -1)
	// 		return (-1);	
	// }
	// step 3
	// current = *commands;
	// remove_heredoc(commands);
	return (0);
}
