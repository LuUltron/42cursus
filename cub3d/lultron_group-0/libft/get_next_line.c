/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:19:19 by lultron           #+#    #+#             */
/*   Updated: 2020/07/19 01:01:38 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list2	*find_fd(t_list2 **backup, const int fd)
{
	t_list2	*new;

	if (*backup == NULL)
		return (*backup = ft_lstnew_2("", fd));
	if (((*backup)->index) == fd)
		return (*backup);
	new = *backup;
	while ((*backup)->prev != NULL && (*backup)->index != fd)
		*backup = (*backup)->prev;
	if (((*backup)->index) == fd)
		return (*backup);
	*backup = new;
	while (((*backup)->next) != NULL && (*backup)->index != fd)
		*backup = (*backup)->next;
	if (((*backup)->next) == NULL && ((*backup)->index) != fd)
	{
		if (!(new = ft_lstnew_2("", fd)))
			return (NULL);
		new->prev = *backup;
		(*backup)->next = new;
		*backup = (*backup)->next;
	}
	return (*backup);
}

static int		copy_to_line(char *bkpcontent, char **line)
{
	char	*rest;
	int		i;

	i = 0;
	rest = NULL;
	while (bkpcontent[i] != '\0')
	{
		if (bkpcontent[i] == '\n')
		{
			rest = bkpcontent + i;
			break ;
		}
		i++;
	}
	if (!rest)
		return (0);
	if (!(*line = ft_substr(bkpcontent, 0, (size_t)i)))
		return (-1);
	ft_strlcpy(bkpcontent, rest + 1, ft_strlen(rest) + 1);
	return (1);
}

static int		last_line(char *bkpcontent, char **line)
{
	if (*bkpcontent != '\0')
	{
		if (!(*line = ft_strdup(bkpcontent)))
			return (-1);
		ft_strlcpy(bkpcontent, bkpcontent + ft_strlen(bkpcontent), 1);
		return (1);
	}
	if (!(*line = ft_strdup(bkpcontent)))
		return (-1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static t_list2	*backup;
	t_list2			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0
		|| !(tmp = find_fd(&backup, fd)))
		return (-1);
	if ((ret = copy_to_line(tmp->content, line)) != 0)
		return (ret < 0 ? ft_lstdelone_2(&backup) : 1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp->content = ft_strjoin_2(tmp->content, buf)))
			return (ft_lstdelone_2(&backup));
		if ((ret = copy_to_line(tmp->content, line)) != 0)
			return (ret < 0 ? ft_lstdelone_2(&backup) : 1);
	}
	if ((ret = last_line(tmp->content, line)) != 1)
		ft_lstdelone_2(&backup);
	return (ret);
}
