/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:51:49 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/06/04 22:03:35 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lit_len;
	size_t	i;

	i = 0;
	lit_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && len > i)
	{
		if (big[i] == *little)
		{
			if (len - i >= lit_len)
			{
				if (ft_strncmp(big + i, little, lit_len) == 0)
					return ((char *)(big + i));
			}
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*a = "adbcdefsss";
	char	*b = "def";

	printf("%s\n", ft_strnstr(a, b, 50));
	printf("%s\n", strnstr(a, b, 50));
	return (0);
}
*/
