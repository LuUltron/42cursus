/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 01:39:49 by lultron           #+#    #+#             */
/*   Updated: 2020/07/30 23:42:56 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putusnbr(long long nbr, int zerowidth)
{
	while (zerowidth--)
		ft_putchar_fd('0', 1);
	if (nbr < 10)
		ft_putchar_fd(nbr + '0', 1);
	else
	{
		ft_putusnbr(nbr / 10, 0);
		ft_putusnbr(nbr % 10, 0);
	}
}

int		print_int_sub(long long nb, t_spcf *format, int len, int zerowidth)
{
	if ((format->flags & MINUS))
	{
		if (format->type == 'm')
			write(1, "-", 1);
		ft_putusnbr(nb, zerowidth);
		len += print_width(format, len);
	}
	else
	{
		if (!(format->flags & ZERO))
			len += print_width(format, len);
		else if (format->width > (unsigned int)len)
		{
			zerowidth = format->width - len;
			len = format->width;
		}
		if (format->type == 'm')
			write(1, "-", 1);
		ft_putusnbr(nb, zerowidth);
	}
	return (len);
}

int		print_int(long long nb, t_spcf *format)
{
	int		len;
	int		zerowidth;

	len = ft_usnbrlen(nb, 10);
	zerowidth = 0;
	if (format->precision != -1 && (format->flags & ZERO))
		format->flags = format->flags ^ ZERO;
	if (nb == 0 && format->precision == 0)
		return (print_width(format, 0));
	if (format->precision > len)
	{
		zerowidth = format->precision - len;
		len = format->precision;
	}
	if (nb < 0)
	{
		len++;
		nb = -nb;
		format->type = 'm';
	}
	len = print_int_sub(nb, format, len, zerowidth);
	return (len);
}

int		print_usint(unsigned int unb, t_spcf *format)
{
	int		len;
	int		zerowidth;

	len = ft_usnbrlen(unb, 10);
	zerowidth = 0;
	if (format->precision != -1 && (format->flags & ZERO))
		format->flags = format->flags ^ ZERO;
	if (unb == 0 && format->precision == 0)
		return (print_width(format, 0));
	if (format->precision > len)
	{
		zerowidth = format->precision - len;
		len = format->precision;
	}
	if ((format->flags & MINUS))
	{
		ft_putusnbr(unb, zerowidth);
		len += print_width(format, len);
	}
	else
	{
		len += print_width(format, len);
		ft_putusnbr(unb, zerowidth);
	}
	return (len);
}
