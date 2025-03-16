/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:13:46 by chanypar          #+#    #+#             */
/*   Updated: 2024/08/05 22:51:07 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_pipes(t_pars **commands)
{
	int		i;
	t_pars	*current;

	i = 0;
	current = (*commands);
	while (current->next)
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	check_heredoc(t_pars **commands)
{
	t_pars	*current;
	int		i;

	i = 0;
	current = *commands;
	while (current)
	{
		if (current->redirections && current->redirections->type == HEREDOC)
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}

int	check_place(t_pars **commands, int place)
{
	t_pars	*current;
	int		i;

	i = 0;
	current = *commands;
	while (current)
	{
		current = current->next;
		i++;
	}
	if (i == place)
		return (1);
	return (0);
}
