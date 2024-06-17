/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:40:37 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/17 16:37:31 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(t_cmds **ret, t_envp **lst)
{
	if (!ft_strcmp((*ret)->name, "cd"))
		ft_cd(*ret, lst);
	else if (!ft_strcmp((*ret)->name, "echo"))
	{
		ft_echo(*ret, ret);
		return (1);
	}
	return (0);
}