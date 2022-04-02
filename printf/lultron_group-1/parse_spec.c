/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:44:49 by lultron           #+#    #+#             */
/*   Updated: 2020/07/29 23:15:59 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*set_flags(char *str, t_spcf *format)
{
	while (*str)
	{
		if (*str == '-')
			format->flags = format->flags | MINUS;
		else if (*str == '0')
		{
			if (!(format->flags & MINUS))
				format->flags = format->flags | ZERO;
		}
		else if (!(ft_strchr(SKIPS, *str)))
			break ;
		str++;
	}
	return (str);
}

char	*set_width(char *str, va_list args, t_spcf *format)
{
	int		value;

	value = 0;
	if (*str == '*')
	{
		value = va_arg(args, int);
		if (value < 0)
		{
			format->flags = ((format->flags | ZERO) ^ ZERO) | MINUS;
			value = -value;
		}
		format->width = value;
		str++;
	}
	else
	{
		while (ft_isdigit(*str))
			format->width = (format->width * 10) + (*str++ - 48);
	}
	return (str);
}

char	*set_precision(char *str, va_list args, t_spcf *format)
{
	if (*str == '.')
	{
		str++;
		format->precision = 0;
		if (*str == '*')
		{
			format->precision = va_arg(args, int);
			if (format->precision < 0)
				format->precision = -1;
			str++;
		}
		else
		{
			while (ft_isdigit(*str))
				format->precision = (format->precision * 10) + (*str++ - 48);
		}
	}
	return (str);
}

char	*parse_specifier(t_spcf *format, char *str, va_list args)
{
	format->flags = NONE;
	format->width = 0;
	format->precision = -1;
	format->type = '\0';
	if (!(str = set_flags(str, format)))
		return (NULL);
	str = set_width(str, args, format);
	str = set_precision(str, args, format);
	if (*str && ft_strchr(TYPES, *str))
	{
		format->type = *ft_strchr(TYPES, *str);
		str++;
	}
	else
		return (NULL);
	return (str);
}
