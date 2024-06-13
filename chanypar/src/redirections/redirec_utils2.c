/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:55:03 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/13 14:09:40 by chanypar         ###   ########.fr       */
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

int	exec_heredoc(t_file **file, int flag)
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
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}

int	execute_command(int i, t_cmds *cmds, t_envp **lst, t_cmds **ret)
{

	(void)ret;
	if (cmds->code_id != 9)
		cmds = cmds->prev;
	if (ft_strcmp(cmds->name, "cd") != 0 && ft_strcmp(cmds->name, "echo") != 0)
		cmds = cmds->prev;
	if (i == 0)
		ft_echo(cmds);
	if (i == 1)
		ft_cd(cmds, lst);
	if (i == 2)
		ft_pwd(cmds, lst);
	if (i == 3)
		ft_export(cmds, lst);
	if (i == 4)
		ft_unset(lst);
	else
	{
		// if (cmds->next)
		// 	execlp(cmds->name, cmds->name, cmds->next->name);
		// else
			// execlp(cmds->name, cmds->name);
	}
	// if (i == 5)
	// 	// env
	// if (i == 6)
	// 	// exit
	return (0);
}
