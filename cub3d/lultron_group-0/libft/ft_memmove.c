/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:07:25 by lultron           #+#    #+#             */
/*   Updated: 2020/05/22 17:03:45 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char		*ptr_s;
	char			*ptr_d;
	size_t			i;

	ptr_s = src;
	ptr_d = dst;
	i = 0;
	if (ptr_d < ptr_s)
	{
		while (i < len)
		{
			ptr_d[i] = ptr_s[i];
			i++;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
