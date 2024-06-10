/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:43:52 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/10 15:02:37 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_cmds *cmd, t_envp **lst)
{
	char	PWD[2048];
	int		len;

	if (!cmd)
		return (1);
	if (!getcwd(PWD, 2048))
		printf("PWD error : %s\n", strerr(errno));
	if (ft_strlen(PWD) + 1 > printf("%s\n", PWD))
		return (printf("error writing\n"), 1);
	return (0);
}
