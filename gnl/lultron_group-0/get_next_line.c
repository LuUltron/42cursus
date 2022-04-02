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

#include "get_next_line.h"

t_list	*ft_lstnew(void *content, int fd)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->current_fd = fd;
	if (!(new->content = ft_strdup((const char *)content)))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_list	*find_fd(t_list **backup, const int fd)
{
	t_list	*new;

	if (*backup == NULL)
		return (*backup = ft_lstnew("", fd));
	if (((*backup)->current_fd) == fd)
		return (*backup);
	new = *backup;
	while ((*backup)->prev != NULL && (*backup)->current_fd != fd)
		*backup = (*backup)->prev;
	if (((*backup)->current_fd) == fd)
		return (*backup);
	*backup = new;
	while (((*backup)->next) != NULL && (*backup)->current_fd != fd)
		*backup = (*backup)->next;
	if (((*backup)->next) == NULL && ((*backup)->current_fd) != fd)
	{
		if (!(new = ft_lstnew("", fd)))
			return (NULL);
		new->prev = *backup;
		(*backup)->next = new;
		*backup = (*backup)->next;
	}
	return (*backup);
}

void	ft_lstdelone(t_list **lst)
{
	t_list	*tmpn;
	t_list	*tmpp;

	if (!*lst)
		return ;
	tmpn = (*lst)->next;
	tmpp = (*lst)->prev;
	free((*lst)->content);
	(*lst)->current_fd = 0;
	free(*lst);
	*lst = NULL;
	if (tmpn)
	{
		*lst = tmpn;
		(*lst)->prev = tmpp;
		if (tmpp)
		{
			*lst = (*lst)->prev;
			(*lst)->next = tmpn;
		}
	}
	else if ((*lst = tmpp))
		(*lst)->next = tmpn;
}

int		copy_to_line(char *bkpcontent, char **line)
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
	*line = ft_substr(bkpcontent, 0, (size_t)i);
	ft_strlcpy(bkpcontent, rest + 1, ft_strlen(rest) + 1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static t_list	*backup;
	t_list			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0
		|| !(tmp = find_fd(&backup, fd)))
		return (-1);
	if (copy_to_line(tmp->content, line))
		return (1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp->content = ft_strjoin_2(tmp->content, buf)))
		{
			ft_lstdelone(&backup);
			return (-1);
		}
		if (copy_to_line(tmp->content, line))
			return (1);
	}
	*line = ft_strdup(tmp->content);
	ft_lstdelone(&backup);
	return (0);
}
