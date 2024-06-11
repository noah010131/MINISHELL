/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:55:03 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/10 15:23:29 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* if CTRL + C, just appear new prompt*/

int	read_heredoc(char *end_str, t_file **file)
{
	FILE	*temp;
	int		fd;
	char	buffer[1024];

	temp = f_open2(".temp_heredoc.txt", file, 13);
	if (!temp)
		return (-1);
	fd = fileno(temp);
	while (1)
	{
		printf("\' ");
		fgets(buffer, 1024, stdin);
		if (ft_strcmp(buffer, end_str) == 0)
			break ;
		fprintf(temp, "%s", buffer);
	}
	if (f_close2(fd, file, temp) == -1)
		return (-1);
	return (0);
}

int	exec_heredoc(t_file **file,
		int command, t_cmds *cmd, t_envp **lst, t_cmds **ret)
{
	FILE	*temp;
	int		stdin_save;
	int		fd;

	temp = f_open2(".temp_heredoc.txt", file, 13);
	if (!temp)
		return (-1);
	fd = fileno(temp);
	if (fd == -1)
		return (-1);
	stdin_save = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	execute_command(command, cmd, lst, ret);
	if (dup2(stdin_save, STDIN_FILENO) == -1)
		return (-1);
	if (f_close2(fd, file, temp) == -1)
		return (-1);
	return (0);
}
