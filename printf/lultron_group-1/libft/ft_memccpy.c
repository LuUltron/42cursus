/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:11:44 by lultron           #+#    #+#             */
/*   Updated: 2020/05/22 13:44:23 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*ptr_s;
	unsigned char	*ptr_d;
	size_t			i;

	ptr_s = (unsigned char *)src;
	ptr_d = (unsigned char *)dst;
	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ptr_d[i] = ptr_s[i];
		if (ptr_s[i] == uc)
			return ((unsigned char *)dst + i + 1);
		i++;
	}
	return (NULL);
}
