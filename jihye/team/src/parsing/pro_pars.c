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

int	keep_pars(t_pars *new, t_token *token)
{
	if (token->type == W)
		return (add_arg(new, token->str));
	else if (token->type == RI)
		return (add_last_redir(new_redir(REDIR_IN_S, token->next->str), new));
	else if (token->type == H)
		return (add_last_redir(new_redir(HEREDOC, token->next->str), new));
	else if (token->type == RO)
		return (add_last_redir(new_redir(REDIR_OUT_S, token->next->str), new));
	else if (token->type == AR)
		return (add_last_redir(new_redir(REDIR_OUT_D, token->next->str), new));
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
