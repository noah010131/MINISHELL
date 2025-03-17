/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:47:18 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/17 00:25:01 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_envp **lst)
{
	t_envp	*current;

	if (!lst)
		return (1);
	current = *lst;
	while (current)
	{
		ft_putstr_fd(current->name, 1);
		write(1, "=", 1);
		if (current->value)
			ft_putendl_fd(current->value, 1);
		else
			write(1, "\n", 1);
		current = current->next;
	}
	return (0);
}
