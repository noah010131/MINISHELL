/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:47:18 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/16 18:17:56 by chanypar         ###   ########.fr       */
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
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
