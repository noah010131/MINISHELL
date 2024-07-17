/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:32:22 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/17 13:53:06 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_han(int sig)
{
	(void)sig;
	printf("\n>");
	g_exit_code = -3;
}

int	print_buff(char *buffer, int filenum)
{
	if (filenum == -1)
		return (-1);
	ft_putstr_fd(buffer, filenum);
	ft_putchar_fd('\n', filenum);
	free(buffer);
	return (0);
}

int	read_heredoc(char *end_str, t_file **file, int flag)
{
	FILE	*temp;
	char	*buffer;

	temp = f_open2(TEMP, file, flag);
	signal(SIGINT, sigint_han);
	while (1)
	{
		buffer = readline(">");
		if (g_exit_code == -3 || buffer == NULL)
		{
			if (g_exit_code == -3)
			return (-1);
			ft_putchar_fd('\n', 1);
			ft_putstr_fd("MINI:  warning: here-document at line 1 delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(end_str, 2);
			ft_putstr_fd("')\n", 2);
			return(f_close2(fileno(temp), file, temp));
		}
		if (ft_strncmp(buffer, end_str, ft_strlen(end_str)) == 0)
			break ;
		if (print_buff(buffer, fileno(temp)) == -1)
			return (-1);
	}
	return (f_close2(fileno(temp), file, temp));
}

int	exec_heredoc(t_file **file, int flag)
{
	FILE	*temp;
	int		stdin_save;
	int		fd;

	temp = f_open2(TEMP, file, 13);
	if (!temp)
		return (-1);
	fd = fileno(temp);
	if (fd == -1)
		return (-1);
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	(*file)->f = temp;
	return (stdin_save);
}
