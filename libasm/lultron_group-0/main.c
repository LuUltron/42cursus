/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <lultron@student.21-school.r>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 02:07:51 by lultron           #+#    #+#             */
/*   Updated: 2020/11/24 00:09:38 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include <stdio.h>
#include <string.h>

# define BUFFER_SIZE 512

static void	ft_strlentest(const char *s)
{
	int	sys;
	int	ft;

	sys = strlen(s);
	ft = ft_strlen(s);
	printf("----- strlen test -----\n");
	printf("s = %s\n", s);
	printf("strlen(s) = %d\n", sys);
	printf("ft_strlen(s) = %d\n", ft);
	if (sys == ft)
		printf("[OK]\n");
	else
		printf("[KO]\n");
	printf("=======================\n\n");
}

void	ft_strcmptest(char *s1, char *s2)
{
	printf("----- strcmp test -----\n");
	printf("strcmp(s1, s2)=%d\n", strcmp(s1, s2));
	printf("ft_strcmp(s1, s2)=%d\n", ft_strcmp(s1, s2));
	printf("strcmp(s1, s1)=%d\n", strcmp(s1, s1));
	printf("ft_strcmp(s1, s1)=%d\n", ft_strcmp(s1, s1));;
	printf("strcmp(s2, s1)=%d\n", strcmp(s2, s1));
	printf("ft_strcmp(s2, s1)=%d\n", ft_strcmp(s2, s1));
	printf("=======================\n\n");
}




static void strcpy_test(const char *src, const char *test)
{

}
static void	ft_strcpytest(const char *src)
{
	char	dst_sys[BUFFER_SIZE];
	char	dst_ft[BUFFER_SIZE];

	bzero(dst_sys, BUFFER_SIZE);
	bzero(dst_ft, BUFFER_SIZE);
	strcpy(dst_sys, src);	
	ft_strcpy(dst_ft, src);
	
	if (!strcmp(dest1, dest2))
		printf("%s :OK\n", test);
	else
		printf("%s :KO\n", test);

	s = s1;
	printf("----- strcpy test -----\n");
	printf("strcpy(s1, s2)=%s\n", strcpy(s, s2));
	printf("ft_strcpy(s1, s2)=%s\n", ft_strcpy(s, s2));
	s = s2;
	printf("strcpy(s2, s1)=%s\n", strcpy(s, s1));
	printf("ft_strcpy(s2, s1)=%s\n", ft_strcpy(s, s1));
	printf("=======================\n\n");
}

int	main(int argc, char **argv)
{
	int i;

	ft_strlentest(argv[1], argv[2]);
	ft_strcmptest(argv[1], argv[2]);
	ft_strcpytest(argv[1], argv[2]);
	printf("===== CRASH TESTS =====\n");
	printf("s1 = NULL; s2 = argv[2]\n");
	ft_strlentest(NULL, argv[2]);
	printf("s1 = NULL; s2 = argv[2]\n");
	ft_strcmptest(NULL, argv[2]);
	printf("s1 = NULL; s2 = argv[2]\n");
	ft_strcpytest(NULL, argv[2]);
	return (0);
}

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>



static void write_test(int fd, char *buf, size_t count, const char *test)
{
    int     or;
    int     ft;
    int		ft_err;
    int		or_err;

    or = write(fd, buf, count);
    or_err = errno;
    ft = ft_write(fd, buf, count);
    ft_err = errno;
    if (or == ft)
        printf("%s : OK\n", test);
    else
        printf("%s :KO\n", test);
    if (ft == -1 || or == -1)
    {
    	if (ft_err == or_err)
    		printf("ERRNO [FT:%d]||[OR:%d] : %s OK\n", ft_err, or_err, test);
    	else
    		printf("ERRNO [FT:%d]||[OR:%d] : %s KO\n", ft_err, or_err, test);
    }
}

static void read_test(int fd, size_t count, const char *test)
{
	int		or;
	int		ft;
	int		ft_err;
	int		or_err;
	char	buf1[BUFFER_SIZE];
	char	buf2[BUFFER_SIZE];

	bzero(buf1, BUFFER_SIZE);
	bzero(buf2, BUFFER_SIZE);
	or = read(fd, buf1, count);
	or_err = errno;
	ft = ft_read(fd, buf2, count);
	ft_err = errno;
	if (or == ft && strcmp(buf1, buf2) == 0)
        printf("%s : OK\n", test);
    else
        printf("%s :KO\n", test);
    if (ft == -1 || or == -1)
    {
    	if (ft_err == or_err)
    		printf("ERRNO [FT:%d]||[OR:%d] : %sOK\n", ft_err, or_err, test);
    	else
    		printf("ERRNO [FT:%d]||[OR:%d] : %sKO\n", ft_err, or_err, test);
    }
}

static void strcmp_test(const char *s1, const char *s2, const char *test)
{
	int		or = strcmp(s1, s2);
	int		ft = ft_strcmp(s1, s2);

	if ((or == 0 && ft == 0) || (or >= 1 && ft >= 1) || (or <= 0 && ft <= 1))
		printf("%s :OK\n", test);
	else
		printf("%s :KO\n", test);
}

static void strdup_test(const char *src, const char *test)
{
	char	*str1;
	char	*str2;

	str1 = ft_strdup(src);
	str2 = strdup(src);
	if (!strcmp(str1, str2))
		printf("%s :OK\n", test);
	else
		printf("%s :KO\n", test);
	free(str1);
	free(str2);
}

int main (void)
{
    printf("FT_WRITE TESTS \n");
	int		fd;

	fd = open("write_tests", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		printf("open() error");
		return 1;
	}
	write_test(fd, "Hello_world\n", 12, "basic");
	write_test(-2, "Hello_world", 11, "bad fd");
	write_test(fd, NULL, 11, "NULL ptr");
	write_test(fd, "Hello_world", -2, "bad len");
	printf("-------------------------------------------------\n");
	/* FT_READ TESTS */
	printf("FT_READ TESTS \n");
	read_test(fd, 12, "basic");
	read_test(-2, 11, "bad fd");
	read_test(fd, 11, "NULL ptr");
	read_test(fd, -2, "bad len");
	if (close(fd) == -1)
	{
		printf("close() error");
		return 1;
	}
	printf("-------------------------------------------------\n");
    /* STRLEN TESTS */ 
    printf("FT_STRLEN TESTS :\n");
	strlen_test("Hello world", "basic1");
	strlen_test("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris tristique dui at tellus blandit vulputate. In hac habitasse platea dictumst. In a nibh ", "long");
	strlen_test("", "empty");
	strlen_test("\n", "new line");
	strlen_test("\n\n", "new line2");
	strlen_test("111+}Te'st!wi/th*[<<As:c2ii3", "strange string");
	strdup_test("FIZZ\0BUZZ", "Unsigned char1");
	strdup_test("\x12\xff", "unsigned char2");
    printf("-------------------------------------------------\n");

    /* FT_STRCMP TESTS */	
	printf("FT_STRCMP TESTS \n");
	strcmp_test("hello World", "hello World", "basic1");
	strcmp_test("hello World", "Hello World", "basic2");
	strcmp_test("hello World", "", "empty1");
	strcmp_test("", "", "empty2");
	strcmp_test("", "Hello world", "empty3");
	strcmp_test("", "\n", "new line 1");
	strcmp_test("\n", "Hello world", "new line 2");
	strcmp_test("\n", "\n", "new line 3");
	strcmp_test("111+}Te'st!wi/th*[<<As:c2ii3", "111+}Te'st!wi/th*[<<As:c2ii3" ,"strange strings");
	strcmp_test("FIZZ\0BUZZ","FIZ\0BUZZ", "Unsigned char1");
	strcmp_test("\x12\xff","\x12\0", "unsigned char2");
	printf("-------------------------------------------------\n");

	/* STRCPY TESTS */ 
    printf("FT_STRCPY TESTS :\n");

    strcpy_test("Hello world", "basic1");
	strcpy_test("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris tristique dui at tellus blandit vulputate. In hac habitasse platea dictumst. In a nibh ", "long");
	strcpy_test("", "empty");
	strcpy_test("\n", "new line");
	strcpy_test("\n\n", "new line2");
	strcpy_test("111+}Te'st!wi/th*[<<As:c2ii3", "strange string");
	strcpy_test("FIZZ\0BUZZ", "Unsigned char1");
	strcpy_test("\x12\xff", "unsigned char2");
	printf("-------------------------------------------------\n");

	/* FT_STRDUP TESTS */
	printf("FT_STRDUP TESTS \n");
	strdup_test("Hello world", "basic1");
	strdup_test("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris tristique dui at tellus blandit vulputate. In hac habitasse platea dictumst. In a nibh ", "long");
	strdup_test("", "empty");
	strdup_test("\n", "new line");
	strdup_test("\n\n", "new line2");
	strdup_test("111+}Te'st!wi/th*[<<As:c2ii3", "strange string");
	strdup_test("FIZZ\0BUZZ", "Unsigned char1");
	strdup_test("\x12\xff", "unsigned char2");
	printf("-------------------------------------------------\n");

    return (0);   
}