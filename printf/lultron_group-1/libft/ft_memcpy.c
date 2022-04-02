/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:17:02 by lultron           #+#    #+#             */
/*   Updated: 2020/05/22 14:14:50 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*ptr_s;
	char		*ptr_d;

	ptr_s = src;
	ptr_d = dst;
	if (dst == 0 && src == 0 && n != 0)
		return (NULL);
	while (n > 0)
	{
		ptr_d[n - 1] = ptr_s[n - 1];
		n--;
	}
	return (dst);
}
