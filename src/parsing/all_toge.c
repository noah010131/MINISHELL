/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_toge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:58:06 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/15 15:39:36 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*free_envp_1(t_envp **lst)
{
	t_envp	*current;
	t_envp	*tmp;

	if (!lst)
		return (NULL);
	if (!(*lst))
		return (free(lst), NULL);
	current = *lst;
	while (current)
	{
		tmp = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = tmp;
	}
	free(lst);
	return (NULL);
}

void	free_pars_ls(t_pars **parsee)
{
	t_pars	*current_p;
	t_pars	*cache_p;
	t_redir	*current_r;
	t_redir	*cache_r;

	if (!parsee)
		return ;
	current_p = *parsee;
	while (current_p)
	{
		current_r = current_p->redirections;
		cache_p = current_p->next;
		freee_error(current_p->arguments);
		free(current_p);
		while (current_r)
		{
			cache_r = current_r->next;
			free(current_r->filename);
			free(current_r);
			current_r = cache_r;
		}
		current_p = cache_p;
	}
	free(parsee);
}

int	free_ori(t_ori *ori)
{
	if (!ori)
		return (0);
	if (ori->cmds)
		free_tcmd(ori->cmds);
	if (ori->envs)
		free_envp_1(ori->envs);
	if (ori->parsee)
		free_pars_ls(ori->parsee);
	if (ori->request)
		free(ori->request);
	return (0);
}

// int	check_pid(t_pars **parsee)
// {
// 	pid_t	pid;
// 	// char	*temp;

// 	if (!ft_strcmp((*parsee)->command, "$$"))
// 	{
// 		pid = getpid();
// 		if ((*parsee)->command)
// 			free((*parsee)->command);
// 		(*parsee)->command = ft_itoa((int)pid);
// 		if (!(*parsee)->command)
// 			return (1);
// 		// temp = NULL;
// 		if ((*parsee)->arguments)
// 		{
// 			if ((*parsee)->arguments[0])
// 				free((*parsee)->arguments[0]);
// 			(*parsee)->arguments[0] = ft_itoa((int)pid);
// 			if (!(*parsee)->arguments[0])
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

int	all_toge(t_ori *ori)
{
	ori->parsee = NULL;
	ori->cmds = split_token(ori->request);
	if (!ori->cmds)
		return (free_ori(ori), 1);
	if (!*(ori->cmds))
		return (free_tcmd(ori->cmds), ft_putstr_fd("syntax error\n", 2), 0);
	code_attr(ori->cmds);
	expanding(ori->cmds, ori->envs);
	if (!ori->cmds)
		return (free_ori(ori), 1);
	ori->cmds = pptreatment(ori->cmds);
	if (!*ori->cmds)
		return (free_tcmd(ori->cmds), ori->parsee = NULL, 0);
	if (!init_state(*(ori->cmds)))
	{
		free_tcmd(ori->cmds);
		ori->parsee = NULL;
		return (0);
	}
	ori->parsee = parser(ori->cmds);
	if (!ori->parsee) //check_pid;
		return (free_ori(ori), 1);
	return (0);
}

// char	**freee_error(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	if (!tab)
// 		return (NULL);
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	if (tab)
// 		free(tab);
// 	return (NULL);
// }