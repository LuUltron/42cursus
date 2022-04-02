/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:02:36 by lultron           #+#    #+#             */
/*   Updated: 2020/08/01 00:02:43 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Assignment name  : inter
// Expected files   : inter.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that takes two strings and displays, without doubles, the
// characters that appear in both strings, in the order they appear in the first
// one.

// The display will be followed by a \n.

// If the number of arguments is not 2, the program displays \n.

// Examples:

// $>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// padinto$
// $>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
// df6ewg4$
// $>./inter "nothing" "This sentence hides nothing" | cat -e
// nothig$
// $>./inter | cat -e
// $

#include <unistd.h>

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	int		k;

	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	while (argv[1][i] != '\0')
	{
		j = 0;
		k = 0;
		while (argv[2][j] != '\0' && k != -1)
		{
			if (argv[1][i] == argv[2][j])
			{
				while (argv[1][k] != argv[1][i] && k < i)
					k++;
				if (k == i)
					write(1, &argv[1][k], 1);
				k = -1;
			}
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
