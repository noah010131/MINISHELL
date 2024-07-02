/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:43:52 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/02 15:49:15 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_cmds *cmd, t_envp **lst)
{
	char	pwd[2048];
	int		len;

	(void)lst;
	(void)len;
	if (!cmd)
		return (1);
	if (!getcwd(pwd, 2048))
		printf("PWD error : %s\n", strerror(errno));
	if (ft_strlen(pwd) + 1 > printf("%s\n", pwd))
		return (printf("error writing\n"), 1);
	return (0);
}
