/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:23:36 by lultron           #+#    #+#             */
/*   Updated: 2020/05/20 17:24:51 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*buff;
	int		i;

	i = ft_strlen(s1);
	buff = (char *)malloc(sizeof(const char) * i + 1);
	if (buff == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	buff[i] = '\0';
	while (--i >= 0)
		buff[i] = s1[i];
	return (buff);
}
