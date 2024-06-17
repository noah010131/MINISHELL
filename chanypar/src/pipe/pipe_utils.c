/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:45:06 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/17 12:43:41 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmds	*make_list(t_cmds *current)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->code_id = current->code_id;
	new->name = current->name;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	set_command(t_cmds **ret, t_cmds ***new_ret, int i, int num)
{
	t_cmds		*current_ret;
	t_cmds		*new;
	int			*pipe_posit;
	int			n;

	current_ret = *(ret);
	n = -1;
	pipe_posit = set_posit(*(ret), num);
	while (i != 0 && ++n < pipe_posit[i] + 1)
		current_ret = current_ret->next;
	*new_ret = malloc(sizeof(t_cmds));
	new = make_list(current_ret);
	if (!*new_ret || !new)
		return (-1);
	**new_ret = new;
	current_ret = current_ret->next;
	while (current_ret && current_ret->code_id != 10)
	{
		new->next = make_list(current_ret);
		new->next->prev = new;
		new = new->next;
		current_ret = current_ret->next;
	}
	free(pipe_posit);
	return (0);
}

int	*set_posit(t_cmds *current, int num)
{
	int		*posit;
	int		i;
	int		times;

	posit = malloc((num + 1) * sizeof(int *));
	if (!posit)
		return (NULL);
	posit[0] = 0;
	i = 0;
	times = 0;
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

int	count_pipes(t_cmds **ret)
{
	int		i;
	t_cmds	*current;

	i = 0;
	current = *(ret);
	while (current->next)
	{
		current = find_name(current, 'p');
		if (!current->code_id)
		{
			free(current);
			return (i);
		}
		if (current->next)
		{
			current = current->next;
			i++;
		}
	}
	return (i);
}
