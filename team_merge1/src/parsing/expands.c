/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:29:25 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/18 00:07:28 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	replace_exp(t_cmds *cmd, t_envp **lst)
{
	int		i;
	char	*str;

	i = 0;
	if (!cmd || !lst)
		return (-1);
	str = cmd->name;
	while (str[i])
	{
		if (str[i] == '$' && ((is_lim_exp(str[i + 1]) == 0) || (str[i
						+ 1] == '?')))
			return (cmd->name = new_expanded(str, str + i, env_match(str + i
						+ 1, lst)), 1);
		if (str[i] == '\'' && interpret(str, str + i) == 1)
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (1);
		}
		else
			i++;
	}
	return (1);
}

void	cp_exp_beg(char **str, char **ret, int *j)
{
	int		i;
	char	*sstr;
	char	*rret;

	i = *j;
	sstr = *str;
	rret = *ret;
	while (sstr[i] && sstr[i] != '$')
	{
		rret[i] = sstr[i];
		i++;
	}
	*j = i;
}

char	*new_expanded(char *str, char *ptr, t_envp *match)
{
	char	*ret;
	char	*cp;
	int		j;
	int		k;

	init_0(&j, &k);
	if (!str || !ptr)
		return (NULL);
	if (!match)
		return (nomatch(ptr, str));
	ret = malloc(ft_strlen(str) + ft_strlen(match->value) + 1);
	if (!ret)
		return (NULL);
	cp_exp_beg(&str, &ret, &j);
	cp = match->value;
	while (cp[k])
		ret[j++] = cp[k++];
	ptr++;
	while (*ptr && is_lim_exp(*ptr) == 0)
		ptr++;
	while (*ptr)
		ret[j++] = *(ptr)++;
	ret[j] = 0;
	free(str);
	return (ret);
}

char	*nomatch(char *ptr, char *str)
{
	int		i;
	int		j;
	char	*new;

	new = ptr;
	i = 0;
	j = 0;
	if (ptr[1] == '?')
		return (rep_ex_sig(str, ptr));
	ptr++;
	while (ptr[i] && !is_lim_exp(ptr[i]))
		i++;
	while (ptr[i])
		new[j++] = ptr[i++];
	new[j] = 0;
	return (str);
}

char	*rep_ex_sig(char *str, char *ptr)
{
	char	*sigar;
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = 0;
	sigar = ft_itoa(g_exit_code);
	if (!sigar)
		return (NULL);
	ret = malloc(ft_strlen(sigar) + ft_strlen(str) + 1);
	if (!ret)
		return (free(sigar), NULL);
	while (&str[j] != ptr)
		ret[i++] = str[j++];
	ptr += 2;
	j = 0;
	while (sigar[j])
		ret[i++] = sigar[j++];
	while (*ptr)
		ret[i++] = *ptr++;
	ret[i] = 0;
	return (free(sigar), free(str), ret);
}
