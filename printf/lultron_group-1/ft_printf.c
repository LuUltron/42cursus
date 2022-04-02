/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:44:49 by lultron           #+#    #+#             */
/*   Updated: 2020/07/30 23:41:40 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_usnbrlen(long long nbr, int sys)
{
	int		res;

	res = 0;
	if (nbr == 0)
		res++;
	while (nbr != 0)
	{
		res++;
		nbr /= sys;
	}
	return (res);
}

int		print_width(t_spcf *format, int offset)
{
	int		len;

	len = 0;
	if (format->width && format->width > (unsigned int)offset)
	{
		while (format->width - offset > 0)
		{
			if ((format->flags & ZERO))
				ft_putchar_fd('0', 1);
			else
				ft_putchar_fd(' ', 1);
			format->width--;
			len++;
		}
	}
	return (len);
}

int		print_specifier(t_spcf *format, va_list args, int outlen)
{
	if (format->type == 'c')
		outlen += print_char(va_arg(args, int), format);
	if (format->type == 's')
		outlen += print_str(va_arg(args, char *), format);
	if (format->type == 'p')
		outlen += print_ptr(va_arg(args, size_t), format);
	if (format->type == 'd' || format->type == 'i')
		outlen += print_int(va_arg(args, int), format);
	if (format->type == 'u')
		outlen += print_usint(va_arg(args, unsigned int), format);
	if (format->type == 'x' || format->type == 'X')
		outlen += print_hex(va_arg(args, unsigned int), format);
	if (format->type == '%')
		outlen += print_char('%', format);
	return (outlen);
}

int		ft_printf(const char *str, ...)
{
	va_list	args;
	int		outlen;
	t_spcf	format;

	if (!str)
		return (-1);
	outlen = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			if (!(str = parse_specifier(&format, (char *)++str, args)))
				return (-1);
			outlen = print_specifier(&format, args, outlen);
		}
		else
		{
			ft_putchar_fd(*str, 1);
			outlen++;
			str++;
		}
	}
	va_end(args);
	return (outlen);
}
