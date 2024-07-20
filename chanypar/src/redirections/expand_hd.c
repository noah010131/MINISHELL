/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:03:08 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/20 13:54:27 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nb_expand_hd(char *str)
{
	if (!str)
		return (-1);
	if (ft_pos_c(str, '$') > -1)
		return (1);
	return (0);
}

char	*replace_exp_hd(char **stri, t_envp **lst)
{
	int		i;
	char	*str;

	i = 0;
	str = *stri;
	if (!str || !lst)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && ((is_lim_exp(str[i + 1]) == 0) || (str[i
					+ 1] == '?')))
			return (new_expanded(str, str + i, env_match(str + i + 1, lst)));
		i++;
	}
	return (str);
}

char	*expanding_hd(char *str, t_envp **envp)
{
	while (nb_expand_hd(str) > 0)
	{
		str = replace_exp_hd(&str, envp);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*free_ret_nul(char *str)
{
	if (str)
		free(str);
	return (NULL);
}