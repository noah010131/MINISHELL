/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:46:45 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/17 08:54:49 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_stock(char *stock)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	i++;
	len = ft_strlen(stock);
	res = ft_calloc((len + i + 1), 1);
	j = 0;
	while (stock[i])
		res[j++] = stock[i++];
	free(stock);
	return (res);
}

char	*free_malloc(char *stock, char *buff)
{
	char	*temp;

	temp = ft_strjoin(stock, buff);
	free(stock);
	return (temp);
}

char	*read_buff(int fd, char *stock)
{
	char	*temp;
	int		i;

	if (!stock)
	{
		stock = malloc(1);
		if (!stock)
			return (0);
		stock[0] = '\0';
	}
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (0);
	temp[0] = '\0';
	i = 1;
	while (i > 0 && (!(ft_strchr(temp, '\n'))))
	{
		i = read(fd, temp, BUFFER_SIZE);
		temp[i] = 0;
		stock = free_malloc(stock, temp);
	}
	free(temp);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*res;
	int			i;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stock = read_buff(fd, stock);
	i = 0;
	if (!stock || !stock[i])
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	while (stock[i] && stock[i] != '\n')
		i++;
	res = ft_calloc(i + 2, 1);
	i = -1;
	while (stock[++i] && stock[i] != '\n')
		res[i] = stock[i];
	if (stock[i] && stock[i] == '\n')
		res[i] = '\n';
	stock = put_stock(stock);
	return (res);
}
