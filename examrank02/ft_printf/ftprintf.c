/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:03:51 by lultron           #+#    #+#             */
/*   Updated: 2020/08/01 00:03:53 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Assignment name  : ft_printf
// Expected files   : ft_printf.c
// Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
// --------------------------------------------------------------------------------

// Write a function named `ft_printf` that will mimic the real printf with the following constraints:

// - It will manage only the following conversions: s,d and x
// - It will manage the minimum field width. (we will never test with a field with of 0)
// - It will manage only the precison flag `.`.

// Your function must be declared as follows:

// int ft_printf(const char *, ... );

// Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
// To test your program compare your results with the true printf.

// Exemples of the function output:

// call: ft_printf("%10.2s\n", "toto");
// out:        to$

// call: ft_printf("Magic %s is %5d", "number", 42);
// out:Magic number is    42%

// call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// out:Hexadecimal for 42 is 2a$

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

typedef struct		s_spcf
{
	unsigned int	width;
	int				precision;
	char			type;
}					t_spcf;

int		print_width(unsigned int width, int offset)
{
	int		len;

	len = 0;
	if (width && width > (unsigned int)offset)
	{
		while (width - offset > 0)
		{
			write(1, " ", 1);
			width--;
			len++;
		}
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
	i = 0;
	while (s[i] != '\0')
		i++;
	len = i;
	if (format->precision >= 0 && format->precision < len)
		len = format->precision;
	i = len;
	len += print_width(format->width, len);
	while (i-- > 0)
		write(1, &(*s++), 1);
	return (len);
}

int		ft_usnbrlen(long long nbr, int system)
{
	int		res;

	res = 0;
	if (nbr == 0)
		res++;
	while (nbr != 0)
	{
		res++;
		nbr /= system;
	}
	return (res);
}

void	ft_putllnbr(long long nbr, int system)
{
	int		digit;
	char	c;

	if (nbr / system != 0)
		ft_putllnbr(nbr / system, system);
	digit = nbr % system;

	if (digit > 9)
		c = digit - 10 + 'a';
	else
		c = digit + '0';
	write(1, &c, 1);
}

int		print_dix(unsigned int ui, t_spcf *format)
{
	int		len;
	int		zerowidth;
	int		system;

	system = 10;
	if (format->type == 'x')
		system = 16;
	len = ft_usnbrlen(ui, system);
	zerowidth = 0;
	if (ui == 0 && format->precision == 0)
		return (print_width(format->width, 0));
	if (format->precision > len)
	{
		zerowidth = format->precision - len;
		len = format->precision;
	}
	
	if (format->type == 'm')
		len++;
	len += print_width(format->width, len);
	if (zerowidth < 0)
		return (len);
	if (format->type == 'm')
		write(1, "-", 1);
	while (zerowidth--)
		write(1, "0", 1);
	ft_putllnbr(ui, system);

	return (len);
}

int		print_int(long long nb, t_spcf *format)
{	
	if (nb < 0)
	{
		nb = -nb;
		format->type = 'm';
	}
	return (print_dix(nb, format));
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
			str++;
			format.width = 0;
			format.precision = -1;
			format.type = '\0';
			while (*str >= '0' && *str <='9')
				format.width = (format.width * 10) + (*str++ - '0');
			if (*str == '.')
			{
				str++;
				format.precision = 0;
				while (*str >= '0' && *str <='9')
					format.precision = (format.precision * 10) + (*str++ - '0');
			}
			format.type = *str;
			if (format.type == 's' || format.type == 'd' || format.type == 'x' || format.type == '%')
			{
				if (format.type == 's')
					outlen += print_str(va_arg(args, char *), &format);
				if (format.type == 'd')
					outlen += print_int(va_arg(args, int), &format);
				if (format.type == 'x')
					outlen += print_dix(va_arg(args, unsigned int), &format);
				if (format.type == '%')
					outlen += print_str("%", &format);
				str++;		
			}
			else
				return (-1);	
		}
		else
		{
			write(1, &(*str), 1);
			outlen++;
			str++;
		}
	}
	va_end(args);
	return (outlen);
}

// int		main(void)
// {
// 	ft_printf("%10.2s\n", "toto");
// 	ft_printf("Magic %s is %5d", "number", 42);
// 	ft_printf("\n");
// 	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// 	printf("==========================expected:==========================\n");
// 	printf("%10.2s\n", "toto");
// 	printf("Magic %s is %5d", "number", 42);
// 	printf("\n");
// 	printf("Hexadecimal for %d is %x\n", 42, 42);
// }

// int		main(void)
// {
// 	int	r;
// 	int	r2;

// 	r = r2 = 0;
// 	printf("|%0.0d||%0.0d|\n", 0, 123);
// 	ft_printf("|%0.0d||%0.0d|\n", 0, 123);
// 	printf("|%0.0x||%0.0x|\n", 0, 123);
// 	ft_printf("|%0.0x||%0.0x|\n", 0, 123);
// 	printf("|%4.0d||%4.0d|\n", 0, 123);
// 	ft_printf("|%4.0d||%4.0d|\n", 0, 123);
// 	printf("|%4.0x||%4.0x|\n", 0, 123);
// 	ft_printf("|%4.0x||%4.0x|\n", 0, 123);
// 	printf("\n=================== Original ===================\n");
// 	r += printf("Simple test\n");
// 	r += printf("");
// 	r += printf("--Format---");
// 	r += printf("\n");
// 	r += printf("%d", 0);
// 	r += printf("%d", 42);
// 	r += printf("%d", 1);
// 	r += printf("%d", 5454);
// 	r += printf("%d", (int)2147483647);
// 	r += printf("%d", (int)2147483648);
// 	r += printf("%d", (int)-2147483648);
// 	r += printf("%d", (int)-2147483649);
// 	r += printf("\n");
// 	printf("===================== Mine =====================\n");
// 	r2 += ft_printf("Simple test\n");
// 	r2 += ft_printf("");
// 	r2 += ft_printf("--Format---");
// 	r2 += ft_printf("\n");
// 	r2 += ft_printf("%d", 0);
// 	r2 += ft_printf("%d", 42);
// 	r2 += ft_printf("%d", 1);
// 	r2 += ft_printf("%d", 5454);
// 	r2 += ft_printf("%d", (int)2147483647);
// 	r2 += ft_printf("%d", (int)2147483648);
// 	r2 += ft_printf("%d", (int)-2147483648);
// 	r2 += ft_printf("%d", (int)-2147483649);
// 	r2 += ft_printf("\n");

// 	printf("\n=================== Original ===================\n");
// 	r += printf("%x", 0);
// 	r += printf("%x", 42);
// 	r += printf("%x", 1);
// 	r += printf("%x", 5454);
// 	r += printf("%x", (int)2147483647);
// 	r += printf("%x", (int)2147483648);
// 	r += printf("%x", (int)-2147483648);
// 	r += printf("%x", (int)-2147483649);
// 	r += printf("%s", "");
// 	r += printf("%s", "toto");
// 	r += printf("%s", "wiurwuyrhwrywuier");
// 	r += printf("%s", NULL);
// 	r += printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
// 	r += printf("%%%%\n");
// 	r += printf("%%%.ddd\n", 12);
// 	printf("===================== Mine =====================\n");
// 	r2 += ft_printf("%x", 0);
// 	r2 += ft_printf("%x", 42);
// 	r2 += ft_printf("%x", 1);
// 	r2 += ft_printf("%x", 5454);
// 	r2 += ft_printf("%x", (int)2147483647);
// 	r2 += ft_printf("%x", (int)2147483648);
// 	r2 += ft_printf("%x", (int)-2147483648);
// 	r2 += ft_printf("%x", (int)-2147483649);
// 	r2 += ft_printf("%s", "");
// 	r2 += ft_printf("%s", "toto");
// 	r2 += ft_printf("%s", "wiurwuyrhwrywuier");
// 	r2 += ft_printf("%s", NULL);
// 	r2 += ft_printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
// 	r2 += ft_printf("%%%%\n");
// 	r2 += ft_printf("%%%.ddd\n", 12);

// 	printf("\n====================Original====================\n");
// 	r += printf("\n--Mixed---\n");
// 	r += printf("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
// 	r += printf("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
// 	r += printf("\n");
// 	r += printf("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
// 	r += printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
// 	printf("===================== Mine =====================\n");
// 	r2 += ft_printf("\n--Mixed---\n");
// 	r2 += ft_printf("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
// 	r2 += ft_printf("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
// 	r2 += ft_printf("\n");
// 	r2 += ft_printf("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
// 	r2 += ft_printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);

// 	printf("\n====================Original====================\n");
// 	r += printf("--1 Flag--\n");
// 	r += printf("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r += printf("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r += printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r += printf("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r += printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	printf("===================== Mine =====================\n");
// 	r2 += ft_printf("--1 Flag--\n");
// 	r2 += ft_printf("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r2 += ft_printf("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r2 += ft_printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r2 += ft_printf("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r2 += ft_printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);

// 	printf("\n====================Original====================\n");
// 	r += printf("--2 Flags--\n");
// 	r += printf("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	printf("===================== Mine =====================\n");
// 	r2 += ft_printf("--2 Flags--\n");
// 	r2 += ft_printf("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);

// 	printf("\n====================Original====================\n");
// 	r += printf("--Precision--\n");
// 	r += printf("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	printf("===================== Mine =====================\n");
// 	r2 += ft_printf("--Precision--\n");
// 	r2 += ft_printf("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);

// 	printf("\n====================Original====================\n");
// 	r += printf("--Width--\n");
// 	r += printf("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r += printf("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	printf("===================== Mine =====================\n");
// 	r2 += ft_printf("--Width--\n");
// 	r2 += ft_printf("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r2 += ft_printf("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);

// 	printf("\n====================Original====================\n");
// 	r += printf("--Width and Precision--\n");
// 	r += printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r += printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r += printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r += printf("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r += printf("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	printf("===================== Mine =====================\n");
// 	r2 += ft_printf("--Width and Precision--\n");
// 	r2 += ft_printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
// 	r2 += ft_printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r2 += ft_printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r2 += ft_printf("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	r2 += ft_printf("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	printf("================================================\n");
// 	printf("written by printf: %d\n", r);
// 	printf("written by ft_printf: %d\n", r2);
// }