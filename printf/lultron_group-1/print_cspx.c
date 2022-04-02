/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cspx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 01:39:49 by lultron           #+#    #+#             */
/*   Updated: 2020/07/29 23:14:30 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_char(int c, t_spcf *format)
{
	int		len;

	len = 1;
	if ((format->flags & MINUS))
	{
		ft_putchar_fd(c, 1);
		len += print_width(format, len);
	}
	else
	{
		len += print_width(format, len);
		ft_putchar_fd(c, 1);
	}
	return (len);
}

int		print_str(char *str, t_spcf *format)
{
	char	*s;
	int		len;
	int		i;

	s = str;
	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	if (format->precision >= 0 && format->precision < len)
		len = format->precision;
	i = len;
	if ((format->flags & MINUS))
	{
		while (--i >= 0)
			ft_putchar_fd(*s++, 1);
		len += print_width(format, len);
	}
	else
	{
		len += print_width(format, len);
		while (--i >= 0)
			ft_putchar_fd(*s++, 1);
	}
	return (len);
}

void	ft_puthexnbr(size_t nbr, int registr, int zerowidth)
{
	int		digit;

	if (zerowidth < 0)
		return ;
	while (zerowidth--)
		ft_putchar_fd('0', 1);
	if (nbr / 16 != 0)
		ft_puthexnbr(nbr / 16, registr, 0);
	digit = nbr % 16;
	if (digit > 9)
		ft_putchar_fd(digit - 10 + registr, 1);
	else
		ft_putchar_fd(digit + '0', 1);
	return ;
}

int		print_ptr(size_t value, t_spcf *format)
{
	int		len;
	int		zerowidth;

	len = ft_usnbrlen(value, 16);
	zerowidth = 0;
	if (format->precision > len || (value == 0 && format->precision == 0))
	{
		zerowidth = format->precision - len;
		len = format->precision;
	}
	if ((format->flags & MINUS))
	{
		write(1, "0x", 2);
		ft_puthexnbr(value, 'a', zerowidth);
		len += print_width(format, len + 2) + 2;
	}
	else
	{
		len += print_width(format, len + 2) + 2;
		write(1, "0x", 2);
		ft_puthexnbr(value, 'a', zerowidth);
	}
	return (len);
}

int		print_hex(unsigned int ui, t_spcf *format)
{
	int		len;
	int		zerowidth;

	len = ft_usnbrlen(ui, 16);
	zerowidth = 0;
	if (format->precision != -1 && (format->flags & ZERO))
		format->flags = format->flags ^ ZERO;
	if (ui == 0 && format->precision == 0)
		return (print_width(format, 0));
	if (format->precision > len)
	{
		zerowidth = format->precision - len;
		len = format->precision;
	}
	if ((format->flags & MINUS))
	{
		ft_puthexnbr(ui, format->type - 23, zerowidth);
		len += print_width(format, len);
	}
	else
	{
		len += print_width(format, len);
		ft_puthexnbr(ui, format->type - 23, zerowidth);
	}
	return (len);
}
