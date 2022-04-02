/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 02:33:28 by lultron           #+#    #+#             */
/*   Updated: 2020/07/23 02:33:58 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define TYPES		"cspdiuxX%"
# define SKIPS		"#+ hlLjzt"
# define NONE		0b00000000
# define MINUS		0b00000001
# define ZERO		0b00000010

typedef struct		s_spcf
{
	unsigned char	flags;
	unsigned int	width;
	int				precision;
	char			type;
}					t_spcf;

int					ft_usnbrlen(long long nbr, int sys);
void				ft_putusnbr(long long nbr, int zerowidth);
void				ft_puthexnbr(size_t nbr, int registr, int zerowidth);
int					print_width(t_spcf *format, int offset);

int					print_char(int c, t_spcf *format);
int					print_str(char *str, t_spcf *format);
int					print_ptr(size_t value, t_spcf*format);
int					print_int_sub(long long nb, t_spcf *format, int len, int z);
int					print_int(long long nb, t_spcf *format);
int					print_usint(unsigned int unb, t_spcf *format);
int					print_hex(unsigned int ui, t_spcf *format);
int					print_specifier(t_spcf *format, va_list args, int outlen);

char				*set_flags(char *str, t_spcf *format);
char				*set_width(char *str, va_list args, t_spcf *format);
char				*set_precision(char *str, va_list args, t_spcf *format);
char				*parse_specifier(t_spcf *format, char *str, va_list args);

int					ft_printf(const char *s, ...);

#endif
