/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:44:17 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/31 15:16:25 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	cd(char **args, t_minishell *minishell)
// {
// 	char	tmp[2048];
// 	char	tmp1[2048];

// 	if (!*args)
// 		return (ft_dprintf(2, "minishell: cd: too few arguments\n"), 1);
// 	if (*(args + 1))
// 		return (ft_dprintf(2, "minishell: cd: too many arguments\n"), 1);
// 	if (!getcwd(tmp, 2048))
// 		return (1);
// 	if (chdir(*args) == -1)
// 		return (ft_dprintf(2, "minishell : cd: %s: %s\n",
// 				*args, strerror(errno)), 1);
// 	if (!getcwd(tmp1, 2048))
// 		return (1);
// 	update_env("OLDPWD", tmp, minishell);
// 	update_env("PWD", getcwd(tmp, 2048), minishell);
// 	return (0);
// }

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
		return (ft_putstr_fd("cd : wrong number of  args\n", 2), 1);
	if (!getcwd(old_pwd, 2048))
		return (1);
	if (chdir(cmd->next->name) == -1)
		return (ft_putstr_fd("error wrong directory\n", 2), 0);
	if (!getcwd(new_pwd, 2048))
		return (1);
	update_env(lst, "PWD", new_pwd);
	update_env(lst, "OLD_PWD", old_pwd);
	// printf("%s\n%s\n", old_pwd, new_pwd);
	return (0);
}
