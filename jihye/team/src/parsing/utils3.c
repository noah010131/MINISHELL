/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:56:02 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/14 20:01:00 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*char	*get_env_suffix(char *str, int *key_end)
{
	char	*space;
	char	*suffix;
	char	*result;

	space = NULL;
	suffix = NULL;
	result = NULL;
	while (str[*key_end] && str[*key_end] != ' '
		&& str[*key_end] != '\t' && str[*key_end] != '\n')
		(*key_end)++;
	if (str[*key_end])
		space = ft_strndup(str + *key_end, 1);
	while (str[*key_end] && (str[*key_end] == ' '
			|| str[*key_end] == '\t' || str[*key_end] == '\n'))
		(*key_end)++;
	suffix = ft_strdup(str + *key_end);
	if (space)
	{
		result = ft_strjoin(space, suffix);
		free(space);
		free(suffix);
		return (result);
	}
	return (suffix);`
}*/

char	*ft_strndup(const char *str, int stop)
{
	int		i;
	char	*result;

	i = 0;
	if (!str || stop < 0)
		return (NULL);
	if (stop > (int)ft_strlen(str))
		stop = (int)ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (stop + 1));
	if (!result)
		return (NULL);
	while (i < stop)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
