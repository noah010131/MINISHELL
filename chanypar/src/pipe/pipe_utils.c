/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:45:06 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/17 12:12:41 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	*set_posit(t_cmds **ret, int num)
{
	int		*posit;
	int		i;
	int		times;
	t_cmds	*current;

	posit = malloc((num + 2) * sizeof(int *));
	if (!posit)
		return (NULL);
	posit[0] = 0;
	i = 0;
	times = 0;
	current = *(ret);
	posit[i] = 0;
	while (++i < num + 1)
	{
		while (current->next && ft_strcmp(current->name, "|"))
		{
			current = current->next;
			times++;
		}
		posit[i] = times;
		current = current->next;
		if (i != num)
			times++;
	}
	return (posit);
}

void	set_pipe(t_cmds **ret, t_envp **list, t_file **file, t_pipe *pipe)
{
	pipe->ret = ret;
	pipe->ret_save = ret;
	pipe->lst = list;
	pipe->file = file;
	pipe->current = *(ret);
}
