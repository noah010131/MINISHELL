/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:44:10 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/18 13:59:43 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_child1(t_envp **lst, t_ori *ori, int free_flag, int files[])
{
	int	i;

	// free(pipe->pids);
	(void)ori;
	i = 0;
	// while (++i < pipe->num_pipes)
	// 	free(pipe->fds[i]);
	// free(pipe->fds);
	while (files && files[i])
	{
		close(files[i]);
		i++;
	}
	if (free_flag)
	{
		free_envp(lst);
		free(lst);
		// free_tori(ori);
	}
}

void	free_child(t_ori *ori, int free_flag, t_pipe *pipe, t_redir *save)
{
	int	i;
	t_redir *current;

	if (pipe)
	{
		free(pipe->pids);
		i = -1;
		while (++i < pipe->num_pipes)
			free(pipe->fds[i]);
		free(pipe->fds);
	}
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
		// free_envp(ori->envs);
		// free(ori->envs);
		// free_tori(ori);
		ori->data
		free_tcmd(ori->cmds);
	// free_pars_ls(ori->parsee);
	if (ori->request)
		free(ori->request);
	}
}
