/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:50:56 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 22:02:36 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_quote(void)
{
	ft_err_print_minishell("Quote is open.");
	exit(EXIT_FAILURE);
}

void	ft_err_print_minishell(char *str)
{
	ft_printf("Error: %s.\n", str);
	exit(EXIT_FAILURE);
}

void	ft_malloc_fail(char *str)
{
	ft_printf("Error: Memory allocation failed in ");
	ft_printf("%s.\n", str);
	exit(EXIT_FAILURE);
}
