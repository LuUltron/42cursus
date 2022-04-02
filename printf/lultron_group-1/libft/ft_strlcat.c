/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 05:53:54 by lultron           #+#    #+#             */
/*   Updated: 2020/05/23 02:05:50 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*d;
	size_t	i;
	size_t	len_d;

	d = dst;
	i = 0;
	while (i++ < size && *d != '\0')
		d++;
	len_d = d - dst;
	if ((size - len_d) != 0)
	{
		i = 0;
		while (src[i] != '\0' && i < (size - len_d - 1))
		{
			dst[i + len_d] = src[i];
			i++;
		}
		dst[i + len_d] = '\0';
	}
	return (len_d + ft_strlen(src));
}
