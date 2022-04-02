/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:27:52 by lultron           #+#    #+#             */
/*   Updated: 2020/05/29 10:18:14 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char		**fill_arr(char **arr, char *str, char c, int cnt)
{
	int		start;
	int		i;
	int		j;

	start = 0;
	i = 0;
	while (i < cnt)
	{
		j = 0;
		while (str[start + j] != c && str[start + j] != '\0')
			j++;
		if (!(arr[i] = (char *)malloc(sizeof(char) * (j + 1))))
		{
			free_arr(arr);
			return (NULL);
		}
		ft_strlcpy(arr[i], str + start, j + 1);
		while ((str[start + j] == c && str[start + j + 1] == c) ||
				(str[start + j] == c && str[start + j + 1] == '\0'))
			j++;
		start = start + j + 1;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char			**ft_split(char const *s, char c)
{
	char	**arr;
	int		cnt;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			cnt++;
		i++;
	}
	if (!(arr = (char **)malloc(sizeof(char *) * (cnt + 1))))
		return (NULL);
	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	arr = fill_arr(arr, (char *)s + i, c, cnt);
	return (arr);
}
