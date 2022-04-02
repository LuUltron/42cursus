/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:20:38 by lultron           #+#    #+#             */
/*   Updated: 2020/11/09 23:04:17 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstdelone_2(t_list2 **lst)
{
	t_list2	*tmpn;
	t_list2	*tmpp;

	if (!*lst)
		return (-1);
	tmpn = (*lst)->next;
	tmpp = (*lst)->prev;
	if ((*lst)->content != NULL)
		free((*lst)->content);
	(*lst)->index = 0;
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
	return (-1);
}
