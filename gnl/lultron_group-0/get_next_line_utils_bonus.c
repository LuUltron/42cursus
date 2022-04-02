/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:20:38 by lultron           #+#    #+#             */
/*   Updated: 2020/07/19 01:00:39 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	size_t		i;

	if (!src)
		return (0);
	s = src;
	if (size != 0)
	{
		i = 0;
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (*src++)
		;
	return (src - s - 1);
}

char	*ft_strdup(const char *s1)
{
	char	*buff;
	int		i;

	i = ft_strlen(s1);
	buff = (char *)malloc(sizeof(const char) * i + 1);
	if (buff == NULL)
	{
		return (NULL);
	}
	buff[i] = '\0';
	while (--i >= 0)
		buff[i] = s1[i];
	return (buff);
}

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

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		len1;
	int		len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(s = (char *)malloc(len1 + len2 + 1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[i - len1] != '\0')
	{
		s[i] = s2[i - len1];
		i++;
	}
	s[i] = '\0';
	return (s);
}
