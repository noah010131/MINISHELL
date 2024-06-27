/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:28:59 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/27 13:41:10 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exit_code(t_status *status, int exit_code)
{
	if (exit_code == 0 && status->isexit == 0)
		return ;
	if (status->isexit)
		exit(exit_code);
}

int	check_flag(int flag, int res)
{
	if (!flag)
		return (res);
	return (flag);
}
void	set_redir_parsing_param(int cpy_stdin_out[])
{
	cpy_stdin_out[0] = 0;
	cpy_stdin_out[1] = 0;
}

int	convert_code(int num)
{
	if (num == 255 || num == -1)
		return (1);
	return (num);
}


int	time_w(void)
{
	struct timespec	req;

	req.tv_sec = 100 / 1000000;
	req.tv_nsec = (100 % 1000000) * 1000;
	return (nanosleep (&req, NULL));
}

