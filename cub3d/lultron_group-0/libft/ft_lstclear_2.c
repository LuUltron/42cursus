/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:20:38 by lultron           #+#    #+#             */
/*   Updated: 2020/11/09 23:03:41 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_2(t_list2 **lst)
{
	t_list2	*tmpn;
	t_list2	*tmpp;

	if ((*lst) == NULL)
		return ;
	tmpp = (*lst)->prev;
	while ((*lst)->next)
	{
		tmpn = (*lst)->next;
		ft_lstdelone_2(lst);
		*lst = tmpn;
	}
	ft_lstdelone_2(lst);
	*lst = tmpp;
	if (!(*lst))
		return ;
	while ((*lst)->prev)
	{
		tmpp = (*lst)->prev;
		ft_lstdelone_2(lst);
		*lst = tmpp;
	}
	ft_lstdelone_2(lst);
	*lst = NULL;
}
