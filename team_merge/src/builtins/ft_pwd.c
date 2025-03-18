/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:43:52 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/17 23:59:55 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	pwd[2048];

	if (!getcwd(pwd, 2048))
		printf("PWD error : %s\n", strerror(errno));
	if ((int)ft_strlen(pwd) + 1 > printf("%s\n", pwd))
		return (printf("error writing\n"), 1);
	return (0);
}
