/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:19:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/04 19:12:33 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	creer une fonction qui va ajouter a la fin de la liste
	un command type :
	elle prendra en parametre le char * de groupe de
	mots en question et int pour le code associe;


	incrementation du pointeur pour le commencement du groupe de mots




*/
// fonction pour identifer les separateurs;
// 1 pour un separateur 0 pour le reste
int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t' || c == '\n')
		return (1);
	if (c == 0)
		return (-1);
	return (0);
}

// fonction similaire a dup mais a une limite pour simplifier le parsing

char	*ft_strlimdup(char *str, int lim)
{
	char	*ret;

	if (!str || !str[0])
		return (NULL);
	ret = ft_strdup(str);
	if (!str)
		return (NULL);
	if (lim >= ft_strlen(ret))
		return (ret);
	ret[lim] = 0;
	return (ret);
}

// fonction principale qui va prendre le resulat de readline
// et va commencer le lexing
// retourne un liste de t_cmd
// retourne null si erreur

t_cmds	**split_token(char *request)
{
	int		i;
	int		j;
	t_cmds	**ret;

	init_1(&i, &j, &ret);
	if (!ret)
		return (NULL);
	*ret = NULL;
	if (syn_err(request) == 1 || !ret)
		return (ret);
	while (request[i])
	{
		if (skip_spcaes(&i, request) == -1)
			return (ret);
		j = go_last_lex(request, i, j);
		ret = ft_last_tcmd(ft_strlimdup(request + i, j), 0, ret);
		reset_sp_tok(&i, &j);
		if (!ret)
			return (free_tcmd(ret), NULL);
		if (!request[i])
			return (ret);
		if (ft_isspace(request[i]))
			i++;
	}
	return (ret);
}

void	reset_sp_tok(int *i, int *j)
{
	*i += *j;
	*j = 0;
}

int	skip_spcaes(int *i, char *request)
{
	while (ft_isspace(request[*i]) && request[*i])
		*i += 1;
	if (!request[*i])
		return (-1);
	return (1);
}
// fonction qui va creer un nouveau token avec le string et le code correspondant
// si erreur retourn null

t_cmds	*ft_new_tcmd(char *str, int code)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->code_id = code;
	new->name = str;
	if (!(new->name))
		return (free(new), NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// fonction qui va prendre un char * et un int et qui va ajouter
// a la fin de la liste le nouveau token correspondant
// si erreur  ou pointeur vide retourne null;
// si liste vide va creer nouvelle

t_cmds	**ft_last_tcmd(char *str, int code, t_cmds **list_cmd)
{
	t_cmds	*current;
	t_cmds	*new;

	current = NULL;
	new = NULL;
	if (!list_cmd)
		return (NULL);
	if (!*list_cmd)
	{
		*list_cmd = ft_new_tcmd(str, code);
		return (list_cmd);
	}
	new = ft_new_tcmd(str, code);
	if (!new)
		return (NULL);
	current = *list_cmd;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	new->next = NULL;
	return (list_cmd);
}
