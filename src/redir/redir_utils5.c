/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:50:53 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 00:14:55 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	expand_file(int src, t_ori *ori)
{
	int		dest_fd;
	char	*buffer;

	dest_fd = open(OUTPUT, O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		buffer = NULL;
		buffer = get_next_line(src);
		if (!buffer)
			break ;
		buffer = expanding_hd(buffer, ori->envs);
		write(dest_fd, buffer, (size_t)ft_strlen(buffer));
		free(buffer);
	}
	close(dest_fd);
	return (dest_fd);
}

int	exec_heredoc(int flag, t_redir	*redirections, t_ori *ori)
{
	int		temp;
	int		stdin_save;

	temp = open(TEMP, O_RDWR, 0644);
	if (!temp)
		return (-1);
	redirections->fd = temp;
	if (redirections->fd == -1)
		return (-1);
	expand_file(redirections->fd, ori);
	close(temp);
	redirections->fd = 0;
	temp = open(OUTPUT, O_CREAT | O_RDWR, 0644);
	if (temp == -1)
		return (-1);
	redirections->fd = temp;
	if (redirections->fd == -1)
		return (-1);
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(redirections->fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}
