/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pro_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:03:27 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/13 23:38:33 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_last_par(t_pars **pars, t_pars *new)
{
	t_pars	*current;

	if (!pars || !new)
		return ;
	if (!*pars)
	{
		*pars = new;
		return ;
	}
	current = *pars;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	keep_pars(t_pars *new, t_cmds *cmd)
{
	// if (cmd->next)
	//     printf("prealable : %s   %s\n", cmd->name, cmd->next->name);
	// else
	//     printf("prealable :    %s\n", cmd->name);
	if (cmd->code_id == WORD)
		return (add_arg(new, cmd->name));
	else if (cmd->code_id == REDIR_IN)
		return (add_last_redir(new_redir(REDIR_IN_S, cmd->next->name), new));
	else if (cmd->code_id == HEREDOC_IN)
		return (add_last_redir(new_redir(HEREDOC, cmd->next->name), new));
	else if (cmd->code_id == REDIR_OUT)
		return (add_last_redir(new_redir(REDIR_OUT_S, cmd->next->name), new));
	else if (cmd->code_id == REDIR_APP)
		return (add_last_redir(new_redir(REDIR_OUT_D, cmd->next->name), new));
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

int	add_arg(t_pars *pars, char *new)
{
	char	**ret;
	int		i;

	i = 0;
	while (pars->arguments && pars->arguments[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (1);
	i = 0;
	while (pars->arguments && pars->arguments[i])
	{
		ret[i] = ft_strdup(pars->arguments[i]);
		if (!ret[i])
			return (freee_error(ret), 1);
		i++;
	}
	ret[i++] = ft_strdup(new);
	ret[i] = 0;
	freee_error(pars->arguments);
	pars->arguments = ret;
	pars->command = ret[0];
	return (0);
}

int	add_last_redir(t_redir *new, t_pars *pars)
{
	t_redir	*current;

	if (!pars || !new)
		return (1);
	if (!pars->redirections)
		pars->redirections = new;
	else
	{
		current = pars->redirections;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}
