/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:39:36 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/13 13:24:40 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redir	*copy(t_pars *command, t_redir *new_redir)
{
	t_redir		*temp;

	temp = (t_redir *)malloc(sizeof(t_redir));
	if (!temp)
	{
		free_redirections(new_redir);
		return (NULL);
	}
	temp->type = command->redirections->type;
	temp->filename = command->redirections->filename;
	temp->fd = 0;
	temp->f = NULL;
	temp->next = NULL;
	return (temp);
}

void	append_redir_node(t_redir **new_redir,
	t_redir *temp, t_redir	**save_new_redir)
{
	if (!*new_redir)
	{
		*new_redir = temp;
		*save_new_redir = *new_redir;
	}
	else
	{
		(*new_redir)->next = temp;
		*new_redir = temp;
	}
}

void	process_heredoc(t_pars *command,
	t_redir **new_redir, t_redir **save_new_redir)
{
	t_redir	*temp;

	while (command->redirections)
	{
		if (command->redirections->type == HEREDOC)
		{
			temp = copy(command, *new_redir);
			append_redir_node(new_redir, temp, save_new_redir);
		}
		command->redirections = command->redirections->next;
	}
}

void	process_non_heredoc(t_pars *command,
	t_redir **new_redir, t_redir **save_new_redir)
{
	t_redir	*temp;

	while (command->redirections)
	{
		if (command->redirections->type != HEREDOC)
		{
			temp = copy(command, *new_redir);
			append_redir_node(new_redir, temp, save_new_redir);
		}
		command->redirections = command->redirections->next;
	}
}

int	create_redir_in_order(t_pars	*command)
{
	t_redir	*new_redir;
	t_redir	*save_redir;
	t_redir	*save_new_redir;

	if (!command->redirections)
		return (0);
	new_redir = NULL;
	save_redir = command ->redirections;
	process_heredoc(command, &new_redir, &save_new_redir);
	command->redirections = save_redir;
	process_non_heredoc(command, &new_redir, &save_new_redir);
	command->redirections = save_redir;
	free_redirections(command->redirections);
	command->redirections = save_new_redir;
	return (0);
}

