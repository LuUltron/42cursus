/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 01:35:07 by lultron           #+#    #+#             */
/*   Updated: 2020/05/28 14:14:43 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (lst)
	{
		ptr = *lst;
		if (ptr)
		{
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
		}
		else
			*lst = new;
	}
}
