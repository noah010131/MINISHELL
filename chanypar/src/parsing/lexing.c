/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:03:59 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/22 21:44:44 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// debut de la fonction qui va servir a attribuer
// un code token a chaque t_cmd
//-1 si erreur
int	code_attr(t_cmds **cmds)
{
	t_cmds	*current;

	if (!cmds)
		return (-1);
	current = *cmds;
	while (current)
	{
		current->code_id = code_lex(current->name);
		current = current->next;
	}
	return (0);
}

int	code_lex(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if (type_quote(str))
		return (type_quote(str));
	if (meta_type(str))
		return (meta_type(str));
	return (WORD);
}

// fonction qui retourne 1 si le mot est entierement
// compose de symboles(meta charatceres)
//-1 si erreur
int	is_not_word(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			return (0);
		i++;
	}
	return (1);
}
// fonction qui retourne le type de
// metacharactere -1 si erreur
int	meta_type(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0 && ft_strlen(str) == 1)
		return (PIPE_N);
	if (ft_strncmp(str, "<", 1) == 0 && ft_strlen(str) == 1)
		return (REDIR_IN);
	if (ft_strncmp(str, ">", 1) == 0 && ft_strlen(str) == 1)
		return (REDIR_OUT);
	if (ft_strlen(str) == 2 && ft_strncmp(str, "<<", 2) == 0)
		return (HEREDOC_IN);
	if (ft_strlen(str) == 2 && ft_strncmp(str, ">>", 2) == 0)
		return (REDIR_APP);
	return (0);
}

// fonction qui retourne le type de quote qui entoure
// le char deja parse
// -1 si erreur
// 0 si il y a pas de quotes
int	type_quote(char *str)
{
	if (!str)
		return (-1);
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (SIN_QUOTE);
	if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		return (DOUB_QUOTE);
	return (0);
}
