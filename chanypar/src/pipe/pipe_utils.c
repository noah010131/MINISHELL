/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:45:06 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/07 15:45:02 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	*set_posit(t_cmds **ret, int num)
{
	int		*posit;
	int		i;
	int		times;
	t_cmds	*current;

	posit = malloc(num * sizeof(int));
	if (!posit)
		return (NULL);
	posit[0] = 0;
	i = -1;
	times = 0;
	while (++i < num)
	{
		while (current->next && ft_strcmp(current->name, "|"))
		{
			current = current->next;
			times++;
		}
		if (current->next)
		{
			posit[i] = times;
			current = current->next;
		}
	}
}

// char	*join_string(char *str, t_cmds **ret, int flag)
// {
// 	char	*temp;

// 	temp = NULL;
// 	if (flag)
// 	{
// 		temp = ft_strjoin(str, " ");
// 		free(str);
// 		str = ft_strdup(temp);
// 		free(temp);
// 	}
// 	temp = ft_strjoin(str,(*ret)->name);
// 	free(str);
// 	str = ft_strdup(temp);
// 	free(temp);
// 	return (str);
// }


// char	*lst_to_char(t_cmds **ret)
// {
// 	t_cmds	*current;
// 	char *str;
// 	int	i;
// 	int flag;
// 	int	len;

// 	i = 0;
// 	str = (char *)malloc(500);
// 	if (!str)
// 		return (NULL);
// 	current = *ret;
// 	while(*ret)
// 	{
// 		len = ft_strlen((*ret)->name);
// 		if (!i)
// 			ft_strlcpy(str, (*ret)->name, len + 1);
// 		else
// 			str = join_string(str, ret, flag);
// 		flag = len;
// 		(*ret) = (*ret)->next;
// 		i++;
// 	}
// 	*ret = current;
// 	printf("%s\n", str);
// 	free(str);
// }

// char	**making_cmds(t_cmds **ret)
// {
// 	char	*str;
// 	char	**split;

// 	str = lst_to_char(ret);
// 	split = ft_split(str, '|');
// 	return (split);
// }

