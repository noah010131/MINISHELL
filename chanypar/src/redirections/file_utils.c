/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:23:58 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/02 15:28:02 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	f_open(char *str, t_file **file)
{
	int	fd;

		fd = open(str, O_RDONLY);
	if (fd != -1)
	{
		if (ft_new_tfile(file, str, fd) == -1)
			return (-1);
	}
	return (fd);
}

FILE	*f_open2(char *str, t_file **file, int redir)
{
	FILE	*f;
	int		fd;

	f = NULL;
	if (redir == 12 )
		f = fopen(str, "wr");
	else if (redir == 13)
		f = fopen(str, "r");
	else if (redir == 14)
		f = fopen(str, "a");
	if (f)
	{
		fd = fileno(f);
		if (ft_new_tfile(file, str, fd) == -1)
			return (NULL);
		return (f);
	}
	return (NULL);
}

int	f_close(int fd, t_file **file)
{
	if (close(fd) == -1)
		return (-1);
	ft_del_tfile(file, fd);
	return (0);
}

int	f_close2(int fd, t_file **file, FILE *f)
{
	if (fclose(f) == -1)
		return (-1);
	ft_del_tfile(file, fd);
	return (0);
}