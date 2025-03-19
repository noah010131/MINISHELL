/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:42:09 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/08/30 03:55:23 by princessj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strlcpy_gnl(char *new_s, char *line, int n_pos)
{
	int	i;

	i = 0;
	if (new_s == NULL || line == NULL)
		return ;
	while (line[n_pos + 1])
	{
		new_s[i] = line[n_pos + 1];
		i++;
		n_pos++;
	}
	new_s[i] = '\0';
}

char	*next_line(char *line)
{
	int		n_pos;
	int		line_len;
	char	*str;

	n_pos = ft_strchr_gnl(line, '\n');
	if (n_pos == -1)
		return (NULL);
	line_len = ft_strlen_gnl(line);
	if ((line_len - n_pos) <= 1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (line_len - n_pos));
	if (!str)
		return (NULL);
	ft_strlcpy_gnl(str, line, n_pos);
	return (str);
}

char	*read_line(int fd, char *next, char *buffer)
{
	int		read_count;

	read_count = 1;
	while (ft_strchr_gnl(next, '\n') == -1 && read_count > 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count == -1)
		{
			free(next);
			next = NULL;
			return (NULL);
		}
		if (read_count == 0)
			break ;
		buffer[read_count] = '\0';
		next = ft_strjoin_gnl(next, buffer);
	}
	return (next);
}

char	*get_line_my(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (free(line), line = NULL, str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*next[1024];

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, 1);
	if (buffer == NULL)
		return (NULL);
	line = read_line(fd, next[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
	{
		next[fd] = NULL;
		return (NULL);
	}
	next[fd] = next_line(line);
	line = get_line_my(line);
	return (line);
}
/*
int	main(int arc, char **argv)
{
	int		fd;
	char	*line;

	(void)arc;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Eroor open file");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}*/
