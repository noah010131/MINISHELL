/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:37:57 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/04 22:04:37 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*str2;
	int		i;

	len = ft_strlen((char *)str);
	str2 = (char *)malloc(sizeof(char) * (len + 1));
	if (str2 == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

/*
int	main(void)
{
	printf("%s\n", ft_strdup("abcd"));
	return (0);
}
*/
