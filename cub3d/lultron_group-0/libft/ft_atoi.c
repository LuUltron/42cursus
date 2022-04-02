/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 14:19:45 by lultron           #+#    #+#             */
/*   Updated: 2020/05/22 03:35:28 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	overflow_check(unsigned long long nb, int sign, char c)
{
	if ((nb > 922337203685477580 && (c >= '0' && c <= '9')) ||
		((c == '8' || c == '9') && nb == 922337203685477580))
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (1);
}

int			ft_atoi(const char *str)
{
	unsigned long long	nb;
	int					sign;

	nb = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
		if (overflow_check(nb, sign, *str) != 1)
			return (overflow_check(nb, sign, *str));
	}
	return (nb * sign);
}
