/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:15:06 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/10 15:01:15 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_error(char *str)
{
	if (ft_occur(str, ' ') != 0)
		return (1);
	if (ft_occur(str, '=') != 1)
		return (1);
	return (0);
}

void	print_export(t_envp *envp)
{
	while (envp)
	{
		if (envp->name && envp->value)
		{
			printf("declare -x %s=", envp->name);
			printf("\"%s\"\n", envp->value);
		}
		else
			printf("declare -x %s\n", envp->name);
		envp = envp->next;
	}
}

int	ft_export(t_cmds *cmds, t_envp **env)
{
	char	*str;

	if (!env)
		return (1);
	if (!cmds)
		return (print_export(*env), 0);
	str = cmds->name;
	if (!str || !*str || export_error(str))
		return (printf("mkshell export bad assignment\n"), 1);
	if (!add_envplast(env, str))
		return (-1);
	return (0);
}
// petit probleme car la fonction de base ne se
// comporte pas comme ailleurs dans le lexing
// a voir
// int	syn_export(char *str)
// {
// 	if (!str)
// 		return (NULL);
// 	int i = 0;
// 	while (ft_isspace(str[i]))
// 		i++;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 			break ;
// 		i++;
// 	}
// 	if (str[i++] != '=')
// 		return (1);
// 	while (str[i])

// }
