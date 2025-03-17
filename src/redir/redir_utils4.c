/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:44:10 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 01:06:09 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_child1(t_envp **lst, t_ori *ori, int free_flag, t_pipe *pipe)
{
	int	i;

	free(pipe->pids);
	i = -1;
	while (++i < pipe->num_pipes)
		free(pipe->fds[i]);
	free(pipe->fds);
	if (free_flag)
	{
		free_envp(lst);
		free(lst);
		free_tori(ori);
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
			fclose(save->f);
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
