/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:39:14 by lultron           #+#    #+#             */
/*   Updated: 2020/08/04 23:59:08 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Assignment name  : get_next_line
// Expected files   : get_next_line.c get_next_line.h
// Allowed functions: read, free, malloc
// --------------------------------------------------------------------------------

// Write a function will store, in the parameter "line", a line that has been read from the file descriptor 0.

// Your function must be prototyped as follows: int get_next_line(char **line);

// Your function should be memory leak free.

// What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).

// The string stored in the parameter "line" should not contained any '\n'.

// The parameter is the address of a pointer to a character that will be used to store the line read.

// The return value can be 1, 0 or -1 depending on whether a line has been read, when the reading has been completed (meaning read has returned 0), or if an error has happened respectively.

// When you've reached the End Of File, you must store the current buffer in "line". If the buffer is empty you must store an empty string in "line".

// When you've reached the End Of File, your function should keep 0 memory allocated with malloc except the last buffer that you should have stored in "line".

// What you've stored in "line" should be free-able.

// Calling your function get_next_line in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.

// Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection etc.

// No call to another function will be done on the file descriptor between 2 calls of get_next_line.

// Finally we consider that get_next_line has an undefined behavior when reading from a binary file.

// You should use the test.sh to help you test your get_next_line.

// #include "gnl.h"

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdio.h> // printf !!remember to del
# include <fcntl.h> // open !!remember to del
# include <unistd.h> // read
# include <stdlib.h> // free, malloc

//int		get_next_line(char **line);
int		get_next_line(int fd, char **line);

#endif

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;

	if (src && size != 0)
	{
		i = 0;
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return ;
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*s;
	int		len1;
	int		len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(s = (char *)malloc(len1 + len2 + 1)))
		return (NULL);
	ft_strlcpy(s, s1, len1 + 1);
	free(s1);
	ft_strlcpy(s + len1, s2, len2 + 1);
	return (s);
}

int		copy_to_line(char *bkp, char **line)
{
	char	*rest;
	int		i;

	i = 0;
	rest = NULL;
	while (bkp[i] != '\0')
	{
		if (bkp[i] == '\n')
		{
			rest = bkp + i;
			break ;
		}
		i++;
	}
	if (!rest)
		return (0);
	if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strlcpy(*line, bkp, i + 1);
	i = ft_strlen(rest);
	ft_strlcpy(bkp, rest + 1, i);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static char		*backup;

	if (!line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	if (!backup)
	{
		if (!(backup = (char *)malloc(1)))
			return (-1);
		*backup = '\0';
	}
	if (copy_to_line(backup, line))
		return (1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(backup = ft_strjoin_2(backup, buf)))
		{
			free(backup);
			return (-1);
		}
		if (copy_to_line(backup, line))
			return (1);
	}
	if (!(*line = (char *)malloc(ft_strlen(backup) + 1)))
	{
		free(backup);
		return (-1);
	}
	ft_strlcpy(*line, backup, ft_strlen(backup) + 1);
	free(backup);
	backup = NULL;
	return (0);
}

int main()
{
	char    		*line;

	int             fd;
	int				fd2;
	int             i;
	int             j;
	
	line = NULL;
	// printf("\n==========================================\n");
	// printf("============== TEST : fd = 0 =============\n");
	// printf("==========================================\n\n");

	// while ((i = get_next_line(0, &line)) > 0)
	// {
	// 	printf("%d|%s\n", i, line);
	// 	free(line);
	// 	line = NULL;
	// }
	// printf("%d|%s", i, line);
	// free(line);
	// line = NULL;

	printf("\n==========================================\n");
	printf("============== TEST : Marge ==============\n");
	printf("==========================================\n\n");

	j = 1;
	if (!(fd = open("half_marge_top", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	if (!(fd2 = open("half_marge_bottom", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("%d|%s\n", i, line);
		free(line);
		j++;
	}
	free(line);
	while ((i = get_next_line(fd2, &line)) > 0)
	{
		printf("%d|%s\n", i, line);
		free(line);
		j++;
	}
	printf("%d|%s\n", i, line);
	free(line);
	close(fd);
	close(fd2);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 25)
		printf("\nRight number of lines\n");
	else if (j != 25)
		printf("\nNot Good - Wrong Number Of Lines\n");

	printf("\n==========================================\n");
	printf("========== TEST : Wrong Input ============\n");
	printf("==========================================\n\n");

	if (get_next_line(180, &line) == -1)
		printf("Well Done, you return -1 if no FD\n\n");
	else
		printf("Not Good, you don't return -1 if no FD\n\n");
	return (0);
}
