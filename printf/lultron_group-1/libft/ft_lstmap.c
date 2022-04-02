/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 02:03:59 by lultron           #+#    #+#             */
/*   Updated: 2020/05/26 01:26:39 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*new_innewl;
	int		i;

	if (!lst && !f)
		return (NULL);
	i = ft_lstsize(lst);
	newlst = NULL;
	while (i > 0)
	{
		if (!(new_innewl = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&newlst, new_innewl);
		i--;
	}
	return (newlst);
}
