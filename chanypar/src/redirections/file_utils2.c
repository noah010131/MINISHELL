/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:17 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/13 11:21:51 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_new_tfile(t_file **file, char file_name[], int fd)
{
	t_file *new;
	static int	isfirst;

	if (!isfirst)
	{
		isfirst = 1;
		// file =  malloc(sizeof(t_file));
		// if (!file)
		// 	return (-1);
	}
	new = malloc(sizeof(t_file));
	if (!new)
		return (-1);
	new->file_name = file_name;
	new->fd = fd;
	new->prev = *(file);
	if (isfirst)
		(*file) = new;
	else
		(*file)->next = new;
	new->next = NULL;
	if (!isfirst)
		(*file) = (*file)->next;
	return (0);
}

void	ft_del_tfile(t_file **file, int fd)
{
	t_file *current;

	current = (*file);
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
}