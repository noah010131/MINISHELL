/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:15:06 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/19 04:07:48 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_error(char *str)
{
	if (ft_occur(str, '=') > 1)
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
			printf("export %s=", envp->name);
			printf("\"%s\"\n", envp->value);
		}
		else
			printf("export %s\n", envp->name);
		envp = envp->next;
	}
}

int	check_exist(char *str, t_envp	**env)
{
	char	*name;
	t_envp	*temp;

	temp = NULL;
	if (!str || !env)
		return (1);
	name = ft_strlimdup(str, ft_pos_c(str, '='));
	if (!name)
		return (1);
	temp = env_match(name, env);
	free(name);
	if (!temp)
	{
		return (0);
	}
	free(temp->value);
	temp->value = ft_strdup(str + ft_pos_c(str, '=') + 1);
	return (1);
}

int	check_no_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_pars *pars, t_envp **env)
{
	char	**str;
	int		i;

	i = 1;
	if (!env || !pars)
		return (1);
	str = pars->arguments;
	if (!str[i])
		return (print_export(*env), 0);
	while (str[i])
	{
		if (!str[i] || !str[i][0] || export_error(str[i]))
			return (write(2, "export: not a valid identifier\n", 31), 1);
		if (check_no_value(str[i]))
			return (0);
		if (ft_occur(str[i], '=') > 0 && !check_exist(str[i], env))
			if (!add_envplast(env, str[i]))
				return (-1);
		if (ft_occur(str[i], '=') == 0)
			if (!add_envplast_null(env, str[i]))
				return (-1);
		i++;
	}
	return (0);
}
