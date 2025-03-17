/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:44:10 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 15:15:53 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_child1(t_envp **lst, t_ori *ori, int free_flag, int files[])
{
	int	i;

	i = 0;
	while (files && files[i])
	{
		close(files[i]);
		i++;
	}
	if (free_flag)
	{
		free_envp(lst);
		free(lst);
		free_tori(ori);
	}
}

void	free_pipe(t_pipe *pipe)
{
	int	i;

	i = -1;
	free(pipe->pids);
	while (++i < pipe->num_pipes)
		free(pipe->fds[i]);
	free(pipe->fds);
}

void	free_child(t_ori *ori, int free_flag, t_pipe *pipe, t_redir *save)
{
	t_redir	*current;

	if (pipe)
		free_pipe(pipe);
	if (free_flag == 2 && save)
	{
		current = (*ori->parsee)->redirections;
		(*ori->parsee)->redirections = save;
		while (save && current != save)
		{
			close(save->fd);
			save = save->next;
		}
	}
	if (free_flag)
	{
		free_envp(ori->envs);
		free(ori->envs);
		free_tori(ori);
	}
}
int	oper_redir_in(t_pars *c, int stdin_save)
{
	if (!stdin_save)
		stdin_save = dup(STDIN_FILENO);
	if (!c->redirections->filename)
		return (check_error_code(c->redirections->filename), -1);
	c->redirections->fd = open(c->redirections->filename, O_RDONLY, 0644);
	if (c->redirections->fd == -1)
		return (check_error_code(c->redirections->filename), -1);
	if (dup2(c->redirections->fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}
