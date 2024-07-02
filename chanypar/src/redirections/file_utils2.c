/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:17 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/02 15:52:14 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_new_tfile(t_file **file, char file_name[], int fd)
{
	t_file		*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (-1);
	new->file_name = file_name;
	new->fd = fd;
	new->f = NULL;
	if ((*file) == NULL)
		new->prev = NULL;
	else
	{
		new->prev = *(file);
		(*file)->next = new;
	}
	if ((*file) == NULL)
		(*file) = new;
	else
		(*file)->next = new;
	new->next = NULL;
	if ((*file)->next)
		(*file) = (*file)->next;
	return (0);
}

void	ft_del_tfile(t_file **file, int fd)
{
	t_file	*current;

	current = *(file);
	while ((*file)->fd != fd)
		(*file) = (*file)->next;
	if ((*file)->prev)
	{
		if ((*file)->next)
			(*file)->prev->next = (*file)->next;
		else
			(*file)->prev->next = NULL; // while fd in looking is a lastlist
	}
	if ((*file)->next)
	{
		if (current->fd == fd) // while fd in looking is a head
		{
			(*file)->next->prev = NULL;
			current = current->next;
		}
		else
			(*file)->next->prev = (*file)->prev;
	}
	(*file) = (*file)->prev;
	free(current);
}

int	close_file(t_file **file, int rv)
{
	while (file && (*file))
	{
		if ((*file)->f)
		{
			if (!(ft_strcmp((*file)->file_name, TEMP)))
				remove(TEMP);
			if (f_close2((*file)->fd, file, (*file)->f) == -1)
				return (-1);
		}
		else
		{
			if (f_close((*file)->fd, file) == -1)
				return (-1);
		}
	}
	free(file);
	return (rv);
}
