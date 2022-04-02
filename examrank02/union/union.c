/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:02:58 by lultron           #+#    #+#             */
/*   Updated: 2020/08/01 00:03:01 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Assignment name  : union
// Expected files   : union.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that takes two strings and displays, without doubles, the
// characters that appear in either one of the strings.

// The display will be in the order characters appear in the command line, and
// will be followed by a \n.

// If the number of arguments is not 2, the program displays \n.

// Example:

// $>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// zpadintoqefwjy$
// $>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
// df6vewg4thras$
// $>./union "rien" "cette phrase ne cache rien" | cat -e
// rienct phas$
// $>./union | cat -e
// $
// $>
// $>./union "rien" | cat -e
// $
// $>

#include <unistd.h>

int	main(int argc, char **argv)
{
	int		i;
	int		k;

	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	while (argv[1][i] != '\0')
	{
		k = 0;
		while (argv[1][k] != argv[1][i] && k < i)
			k++;
		if (k == i)
			write(1, &argv[1][i], 1);
		i++;
	}
	i = 0;
	while (argv[2][i] != '\0')
	{
		k = 0;
		while (argv[1][k] != argv[2][i] && argv[1][k] != '\0')
			k++;
		if (argv[1][k] != argv[2][i])
		{
			k = 0;
			while (argv[2][k] != argv[2][i] && k < i)
				k++;
			if (k == i)
				write(1, &argv[2][i], 1);
		}	
		i++;
	}
	write(1, "\n", 1);
	return (0);
}