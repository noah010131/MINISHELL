/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:56:02 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 11:11:35 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_space_token(t_token_list **token_list)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	if (!token_list || !*token_list)
		return ;
	curr = (*token_list)->bottom;
	while (curr)
	{
		prev = curr->prev;
		next = curr->next;
		if (curr->type == S)
		{
			if (curr->next)
				next->prev = curr->prev;
			if (curr->prev)
				prev->next = curr->next;
			free_token(&curr);
			(*token_list)->cnt--;
		}
		curr = prev;
	}
}

char	*get_suffix(char *curr, int dollar)
{
	int		start;
	int		key_end;
	char	*suffix;

	key_end = dollar;
	start = key_end;
	// printf("get suffix START : [%c]\n", curr[key_end]);
	while (curr[key_end])
		key_end++;
	suffix = ft_strndup((curr + start), (key_end - start));
	if (!suffix)
	{
		if (!curr[key_end])
			return (NULL);
		ft_malloc_fail("get suffix");
		return (NULL);
	}
	return (suffix);
}

/*char	*get_suffix(char *curr, int dollar)
{
	int		start;
	int		key_end;
	char	*suffix;

	key_end = dollar + 1;
	start = key_end;
	// printf("get suffix key_end : [%c]\n", curr[key_end]);
	while (curr[key_end] && curr[key_end] != ' ' && curr[key_end] != '\t'
		&& curr[key_end] != '\n' && curr[key_end] != '$')
		key_end++;
	suffix = ft_strdup(curr + start);
	// printf("get suffix key_end : [%c]\n", curr[key_end]);
	// printf("%c\n", curr[start]);
	// suffix = ft_strndup((curr + start), (key_end - start));
	if (!suffix)
	{
		if (!curr[key_end])
			return (NULL);
		ft_malloc_fail("get suffix");
		return (NULL);
	}
	return (suffix);
}*/

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

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

int	ft_occur(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
