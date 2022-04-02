/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:05:30 by lultron           #+#    #+#             */
/*   Updated: 2020/05/14 01:54:56 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	usc;
	char			*ptr;

	usc = c;
	ptr = b;
	while (len > 0)
	{
		ptr[len - 1] = usc;
		len--;
	}
	return (b);
}
