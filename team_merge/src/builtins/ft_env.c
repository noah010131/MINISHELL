/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:47:18 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/17 23:51:30 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
