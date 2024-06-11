/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:45:06 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/11 16:42:11 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	*set_posit(t_cmds **ret, int num)
{
	int		*posit;
	int		i;
	int		times;
	t_cmds	*current;

	posit = malloc(num * sizeof(int));
	if (!posit)
		return (NULL);
	posit[0] = 0;
	i = -1;
	times = 0;
	current = *(ret);
	while (++i < num)
	{
		while (current->next && ft_strcmp(current->name, "|"))
		{
			current = current->next;
			times++;
		}
		if (current->next)
		{
			posit[i] = times;
			current = current->next;
		}
	}
	return (posit);
}

void	set_pipe(t_cmds **ret, t_envp **list, t_file **file, t_pipe *pipe)
{
	pipe->ret = ret;
	pipe->lst = list;
	pipe->file = file;
	pipe->current = *(ret);
}

// char	**making_cmds(t_cmds **ret)
// {
// 	char	*str;
// 	char	**split;

// 	str = lst_to_char(ret);
// 	split = ft_split(str, '|');
// 	return (split);
// }

