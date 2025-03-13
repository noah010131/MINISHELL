/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:39:36 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/12 23:38:44 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redir *copy(t_pars *command, t_redir *new_redir)
{
	t_redir *temp = (t_redir *)malloc(sizeof(t_redir));
	if (!temp)
	{
		free_redirections(new_redir);
		return (NULL);
	}
	temp->type = command->redirections->type;
	temp->filename = command->redirections->filename;
	temp->fd = command->redirections->fd;
	if (command->redirections->f != 0)
		temp->f = command->redirections->f;
	else
		temp->f = NULL;
	temp->next = NULL;
	return (temp);
}

void	append_redir_node(t_redir *new_redir, t_redir *temp)
{
	if (!new_redir)
		new_redir = temp;
	else
	{
		(new_redir)->next = temp;
		new_redir = temp;
	}
}

int	create_redir_in_order(t_pars	*command)
{
	t_redir	*new_redir;
	t_redir	*temp;
	t_redir	*save_redir;
	t_redir	*save_new_redir;

	if (!command->redirections)
		return (0);
	new_redir = NULL;
	save_redir = command ->redirections;
	while (command->redirections)
	{
		if (command->redirections->type == HEREDOC)
		{
			temp = copy(command, new_redir);
			// append_redir_node(new_redir, temp);
			if (!new_redir)
			{
				new_redir = temp;
				save_new_redir = new_redir;
			}
			else
			{
				new_redir->next = temp;
				new_redir = new_redir->next;
			}
		}
		command->redirections = command->redirections->next;
	}
	command->redirections = save_redir;
	while (command->redirections)
	{
		if (command->redirections->type != HEREDOC)
		{
			temp = copy(command, new_redir);
			if (!new_redir)
			{
				new_redir = temp;
				save_new_redir = new_redir;
			}
			else
			{
				new_redir->next = temp;
				new_redir = new_redir->next;
			}
		}
		command->redirections = command->redirections->next;
	}
	command->redirections = save_redir;
	free_redirections(command->redirections);
	command->redirections = save_new_redir;
	return (0);
}

t_pars	*create_redir_in_order1(t_pars	*command)
{
	t_redir	*new_redir;
	t_redir	*temp;
	t_redir	*save_redir;
	t_redir	*save_new_redir;

	if (!command->redirections)
		return (0);
	new_redir = NULL;
	save_redir = command ->redirections;
	while (command->redirections)
	{
		if (command->redirections->type == HEREDOC)
		{
			temp = copy(command, new_redir);
			// append_redir_node(new_redir, temp);
			if (!new_redir)
			{
				new_redir = temp;
				save_new_redir = new_redir;
			}
			else
			{
				new_redir->next = temp;
				new_redir = new_redir->next;
			}
		}
		command->redirections = command->redirections->next;
	}
	command->redirections = save_redir;
	while (command->redirections)
	{
		if (command->redirections->type != HEREDOC)
		{
			temp = copy(command, new_redir);
			if (!new_redir)
			{
				new_redir = temp;
				save_new_redir = new_redir;
			}
			else
			{
				new_redir->next = temp;
				new_redir = new_redir->next;
			}
		}
		command->redirections = command->redirections->next;
	}
	command->redirections = save_redir;
	free_redirections(command->redirections);
	command->redirections = save_new_redir;
	return (command);
}
