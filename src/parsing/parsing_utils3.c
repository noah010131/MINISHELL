/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:39:42 by chanypar          #+#    #+#             */
/*   Updated: 2025/03/13 23:44:03 by chanypar         ###   ########.fr       */
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

// retourne les erreurs de syntaxe
// 1 pour une erreur 0 si tout va bien

int	syn_err(char *str)
{
	if (!str)
		return (1);
	if (non_print(str) == 1)
		return (1);
	if (open_quote(str) == 1)
		return (1);
	if (tok_acc(str) == 1)
		return (1);
	return (0);
}