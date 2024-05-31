/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:07:07 by chanypar          #+#    #+#             */
/*   Updated: 2024/05/31 16:33:21 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_builtins(t_cmds **ret, t_envp **lst)
{
	if (!ft_strcmp((*ret)->name, "cd"))
		ft_cd(*ret, lst);
	else if (!ft_strcmp((*ret)->name, "echo"))
	{
		ft_echo(*ret);
		return (1);
	}
	return (0);
}

