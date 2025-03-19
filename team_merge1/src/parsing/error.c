/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:50:56 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/17 16:58:30 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_err_print_minishell(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	g_exit_code = 258;
}

void	open_quote(t_data *data)
{
	ft_err_print_minishell("Quote is open.");
	data->token_list->open_quote_flag = ERR;
}

void	ft_malloc_fail(char *str)
{
	ft_printf("Error: Memory allocation failed in %s.\n", str);
	exit(EXIT_FAILURE);
}

void	ft_syntax_err(char *str)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'", 2);
	ft_putendl_fd("\'", 2);
	g_exit_code = 258;
}
