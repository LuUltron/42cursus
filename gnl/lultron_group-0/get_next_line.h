/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:21:27 by lultron           #+#    #+#             */
/*   Updated: 2020/07/19 01:05:47 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# if BUFFER_SIZE < 1
#  error
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	int				current_fd;
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

int					get_next_line(int fd, char **line);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin_2(char *s1, char *s2);
t_list				*ft_lstnew(void *content, int fd);
void				ft_lstdelone(t_list **lst);

#endif
