/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:49:20 by lultron           #+#    #+#             */
/*   Updated: 2020/05/28 14:18:07 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buff;

	buff = malloc(count * size);
	if (buff == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_bzero(buff, count * size);
	return (buff);
}
