/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:44:17 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/02 15:48:19 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_cmds *cmd, t_envp **lst)
{
	char	old_pwd[2048];
	int		i;
	t_cmds	*current;
	char	new_pwd[2048];

	i = 0;
	if (!cmd)
		return (ft_putstr_fd("erreur cd\n", 2), 1);
	current = cmd;
	while (current)
	{
		current = current->next;
		i++;
	}
	if (i != 2)
		return (ft_putstr_fd("cd : too many arguments\n", 2), 1);
	if (!getcwd(old_pwd, 2048))
		return (1);
	if (chdir(cmd->next->name) == -1)
		return (ft_putstr_fd("cd : No such file or directory\n", 2), 1);
	if (!getcwd(new_pwd, 2048))
		return (1);
	update_env(lst, "PWD", new_pwd);
	update_env(lst, "OLD_PWD", old_pwd);
	return (0);
}
