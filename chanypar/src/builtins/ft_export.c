/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:15:06 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/02 15:48:44 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bad_id(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	if (!str)
		return (1);
	if (!(ft_isalpha(str[0]) || str[i] == '_'))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
			&& str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	export_error(char *str)
{
	if (ft_occur(str, '=') != 1)
		return (1);
	if (bad_id(str))
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
	if (!cmds->next)
		return (print_export(*env), 0);
	str = cmds->next->name;
	if (!str || !*str || export_error(str) || cmds->next->next)
		return (ft_putstr_fd("mkshell export bad assignment\n", 2), 1);
	if (!add_envplast(env, str))
		return (-1);
	return (0);
}

