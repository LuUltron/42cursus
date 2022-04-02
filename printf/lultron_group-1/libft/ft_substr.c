/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 20:32:33 by lultron           #+#    #+#             */
/*   Updated: 2020/07/29 23:10:55 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	sz;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		str = ft_strdup("");
	else
	{
		sz = ((ft_strlen(s) - start) > len) ? len : (ft_strlen(s) - start);
		str = (char *)malloc(sizeof(char) * sz + 1);
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, s + start, len + 1);
	}
	return (str);
}
