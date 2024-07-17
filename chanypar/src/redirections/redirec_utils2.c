/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:55:03 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/17 12:11:33 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec(char *command, char **argv, t_cmds **ret, char *check)
{
	int	pid;
	int	status;

	(void)ret;
	g_exit_code = -2;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		execve(command, argv, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		status = check_exec(command, WEXITSTATUS(status), check);
		free(command);
		free(argv);
		return (status);
	}
	return (0);
}
t_cmds	*check_redir_in_lst(t_cmds *c, t_cmds **ret)
{
	if (c->code_id >= 11 & c->code_id <= 14)
		{
			c = c->next;
			if (ft_strcmp(c->name, (*(*ret)->file)->file_name) == 0)
				c = c->next;
		}
	return (c);
}

int	exec_command(t_cmds *c, t_cmds **ret)
{
	char	**argv;
	char	*command;
	int		i;	

	argv = NULL;
	if (c->code_id == 0 || (c->code_id >= 11 && c->code_id <= 14))
		return (0);
	argv = malloc(100);
	if (!argv)
		return (-1);
	i = 0;
	command = put_path(c, ret);
	while (c)
	{
		c = check_redir_in_lst(c, ret);
		argv[i++] = c->name;
		if (!c->next || (c->next->code_id != 9 && c->next->code_id != 21))
			break ;
		c = c->next;
	}
	argv[i] = NULL;
	return (exec(command, argv, ret, c->name));
}
