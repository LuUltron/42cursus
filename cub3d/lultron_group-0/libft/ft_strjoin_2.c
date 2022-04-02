/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:20:38 by lultron           #+#    #+#             */
/*   Updated: 2020/11/09 23:04:42 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
