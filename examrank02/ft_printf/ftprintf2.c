/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:03:51 by lultron           #+#    #+#             */
/*   Updated: 2020/08/06 11:41:27 by lultron          ###   ########.fr       */
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

#ifndef REAL
# define F r+=ft_printf
#else
# define F r+=printf
#endif

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

int		print_str(char *str, unsigned int width, int precision)
{
	int		len;
	int		i;

	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i] != '\0')
		i++;
	len = i;
	if (precision >= 0 && precision < len)
		len = precision;
	i = len;
	len += print_width(width, len);
	while (--i >= 0)
		write(1, &(*str++), 1);
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
	{
		c = digit - 10 + 'a';
		write(1, &c, 1);
	}
		
	else
	{
		c = digit + '0';
		write(1, &c, 1);
	}
    
	return ;
}

int		print_dix(unsigned int ui, unsigned int width, int precision, char type)
{
	int		len;
	int		zerowidth;
	int		system;

	system = 10;
	if (type == 'x')
		system = 16;
	len = ft_usnbrlen(ui, system);
	zerowidth = 0;
	if (ui == 0 && precision == 0)
		return (print_width(width, 0));
	if (precision > len)
	{
		zerowidth = precision - len;
		len = precision;
	}
	
	if (type == 'm')
		len++;
	len += print_width(width, len);
	if (zerowidth < 0)
		return (len);
	if (type == 'm')
		write(1, "-", 1);
	while (zerowidth--)
		write(1, "0", 1);
	ft_putllnbr(ui, system);

	return (len);
}

int		print_int(long long nb, unsigned int width, int precision, char type)
{	
	if (nb < 0)
	{
		nb = -nb;
		type = 'm';
	}
	return (print_dix(nb, width, precision, type));
}

int		ft_printf(const char *str, ...)
{
	va_list     	args;
	int		        outlen;
	unsigned int    width;
    int             precision;
    char            type;

	if (!str)
		return (-1);
	outlen = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			width = 0;
			precision = -1;
			type = '\0';
			while (*str >= '0' && *str <='9')
				width = (width * 10) + (*str++ - '0');
			if (*str == '.')
			{
				str++;
				precision = 0;
				while (*str >= '0' && *str <='9')
					precision = (precision * 10) + (*str++ - '0');
			}
			type = *str;
			if (type == 's' || type == 'd' || type == 'x' || type == '%')
			{
				if (type == 's')
					outlen += print_str(va_arg(args, char *), width, precision);
				if (type == 'd')
					outlen += print_int(va_arg(args, int), width, precision, type);
				if (type == 'x')
					outlen += print_dix(va_arg(args, unsigned int), width, precision, type);
                if (type == '%')
                    outlen += print_str("%", width, precision);
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

 int		main(void)
 {
    //ft_printf("%0.d %2147483647.d\n", 0, 12345);
    //ft_printf("%0.x %2147483647.x\n", 0, 12345);
    ft_printf("%%%2147483647.ddd\n", 12345);
    //printf("%0.d %2147483647.d\n", 0, 12345);
    //printf("%0.x %2147483647.x\n", 0, 12345);
    printf("%%%2147483647.ddd\n", 12345);
    printf("=============================================================\n");
 	ft_printf("%10.2s\n", "toto");
 	ft_printf("Magic %s is %5d", "number", 42);
 	ft_printf("\n");
 	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
 	printf("==========================expected:==========================\n");
 	printf("%10.2s\n", "toto");
 	printf("Magic %s is %5d", "number", 42);
 	printf("\n");
 	printf("Hexadecimal for %d is %x\n", 42, 42);
 }

//int		main(void)
//{
//	int	r;
//
//	r = 0;
//	F("Simple test\n");
//	F("");
//	F("--Format---");
//	F("\n");
//	F("%d", 0);
//	F("%d", 42);
//	F("%d", 1);
//	F("%d", 5454);
//	F("%d", (int)2147483647);
//	F("%d", (int)2147483648);
//	F("%d", (int)-2147483648);
//	F("%d", (int)-2147483649);
//	F("\n");
//	F("%x", 0);
//	F("%x", 42);
//	F("%x", 1);
//	F("%x", 5454);
//	F("%x", (int)2147483647);
//	F("%x", (int)2147483648);
//	F("%x", (int)-2147483648);
//	F("%x", (int)-2147483649);
//	F("%s", "");
//	F("%s", "toto");
//	F("%s", "wiurwuyrhwrywuier");
//	F("%s", NULL);
//	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
//	F("\n--Mixed---\n");
//	F("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
//	F("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
//	F("\n");
//	F("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
//	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
//	F("--1 Flag--\n");
//	F("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("--2 Flags--\n");
//	F("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("--Precision--\n");
//	F("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("--Width--\n");
//	F("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("--Width and Precision--\n");
//	F("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	F("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	F("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	printf("written: %d\n", r);
//}
