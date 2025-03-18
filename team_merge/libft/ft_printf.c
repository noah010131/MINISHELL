/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:21:26 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/09/19 18:26:14 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_p(void *ptr)
{
	uintptr_t	*nbr;
	int			count;

	count = 2;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	nbr = (uintptr_t *)ptr;
	return (count + ft_format_x((unsigned long)nbr, "0123456789abcdef"));
}

int	ft_format_check(const char *format, va_list ap)
{
	int	len;

	len = 0;
	if (*format == 'c')
		len = ft_format_c(va_arg(ap, int));
	else if (*format == 's')
		len = ft_format_s(va_arg(ap, char *));
	else if (*format == 'p')
		len = ft_format_p(va_arg(ap, void *));
	else if (*format == 'd' || *format == 'i')
		len = ft_format_di(va_arg(ap, int));
	else if (*format == 'u')
		len = ft_format_u(va_arg(ap, unsigned int));
	else if (*format == 'x')
		len = ft_format_x(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (*format == 'X')
		len = ft_format_x(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (*format == '%')
	{
		write(1, "%", 1);
		len++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		i;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	i = 0;
	len = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			write(1, format + i, 1);
			len++;
		}
		else if (format[i] == '%')
		{
			i++;
			len += ft_format_check(format + i, ap);
		}
		i++;
	}
	va_end(ap);
	return (len);
}
/*
int	main(void)
{
	printf("%s", "12");
	ft_printf("%s", "12");
	return (0);
}
*/
