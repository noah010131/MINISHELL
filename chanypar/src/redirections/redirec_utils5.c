/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:32:22 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/16 17:47:50 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*pathfinder(char *cmd, char **path_t)
{
	int		i;
	char	*cmd_temp;
	char	*add_slash;

	if (!path_t)
		return (NULL);
	i = 0;
	add_slash = ft_strjoin("/", cmd);
	if (!add_slash)
		return (0);
	while (path_t[i])
	{
		cmd_temp = ft_strjoin(path_t[i], add_slash);
		if (!cmd_temp)
			return (free(add_slash), NULL);
		if (access(cmd_temp, F_OK) == 0)
			return (free(add_slash), cmd_temp);
		free(cmd_temp);
		i++;
	}
	free(add_slash);
	return (NULL);
}

char	*put_path(t_cmds *c, t_cmds **ret)
{
    int     i;
    char	**temp_path;
	char	*path;
    
    i = 0;
    if (access(c->name, F_OK) == 0)
		return(ft_strdup(c->name));
	else
	{
		while ((*ret)->env[i])
		{
			if (ft_strncmp((*ret)->env[i], "PATH", 4) == 0)
				break ;
			i++;
		}
		if ((*ret)->env[i] == NULL)
			exit(1);
		temp_path = ft_split((*ret)->env[i], ':');
		path = pathfinder(c->name, temp_path);
	}
    return (path);
}
