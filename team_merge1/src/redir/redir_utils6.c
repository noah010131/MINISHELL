/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:02:36 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 04:28:14 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_parsing(int std_s[], t_ori *ori, t_pipe *pipe, t_redir *save)
{
	if (!(*ori->parsee)->redirections)
		return (0);
	if ((*ori->parsee)->redirections->type == REDIR_IN_S)
		std_s[0] = ch_err(oper_redir_in(*ori->parsee, std_s[0]), std_s);
	else if ((*ori->parsee)->redirections->type == REDIR_OUT_S)
		std_s[1] = ch_err(oper_redir_out(*ori->parsee, std_s[1]), std_s);
	else if ((*ori->parsee)->redirections->type == HEREDOC)
		std_s[0] = ch_err(oper_heredoc_in(std_s[0], ori, pipe, save), std_s);
	else if ((*ori->parsee)->redirections->type == REDIR_OUT_D)
		std_s[1] = ch_err(oper_redir_app(*ori->parsee, std_s[1]), std_s);
	if (std_s[0] < 0)
		return (std_s[0]);
	if (std_s[1] < 0)
		return (std_s[1]);
	return (0);
}

char	**freee_error(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}
