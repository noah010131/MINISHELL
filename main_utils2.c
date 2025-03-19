/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:33:15 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/19 16:37:34 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_all_all(t_data *data, char **prompt, t_envp **lst)
{
	free_envp(lst);
	free(lst);
	free_all(data, prompt);
}
