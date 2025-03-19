/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:03:08 by ihibti            #+#    #+#             */
/*   Updated: 2025/03/19 11:02:43 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*nomatch_hd(char *ptr, char *str)
{
	int		i;
	int		j;
	char	*new;

	new = ptr;
	i = 0;
	j = 0;
	if (ptr[1] == '?')
		return (rep_ex_sig_hd(str, ptr));
	ptr++;
	while (ptr[i] && !is_lim_exp(ptr[i]))
		i++;
	while (ptr[i])
		new[j++] = ptr[i++];
	new[j] = 0;
	return (ft_strdup(str));
}

char	*rep_ex_sig_hd(char *str, char *ptr)
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
	return (free(sigar), ret);
}

int	exp_exception_hd(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && (!is_lim_exp(str[i + 1]) || str[i + 1] == '?'))
			count++;
		i++;
	}
	return (count);
}

char	*new_expanded_hd(char *str, char *ptr, t_envp *match)
{
	char	*ret;
	char	*cp;
	int		j;
	int		k;

	init_0(&j, &k);
	if (!str || !ptr)
		return (NULL);
	if (!match)
		return (nomatch_hd(ptr, str));
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
	return (ret);
}
