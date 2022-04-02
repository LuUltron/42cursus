/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 01:53:49 by lultron           #+#    #+#             */
/*   Updated: 2020/05/28 14:23:57 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (lst != NULL && del != NULL)
	{
		while ((*lst))
		{
			ptr = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = ptr;
		}
		*lst = NULL;
	}
}
