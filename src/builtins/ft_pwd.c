/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:43:52 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/30 15:56:04 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	pwd[2048];

	if (!getcwd(pwd, 2048))
		printf("PWD error : %s\n", strerror(errno));
	if (ft_strlen(pwd) + 1 > printf("%s\n", pwd))
		return (printf("error writing\n"), 1);
	return (0);
}
