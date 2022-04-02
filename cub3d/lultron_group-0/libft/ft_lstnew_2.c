/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:20:38 by lultron           #+#    #+#             */
/*   Updated: 2020/11/09 23:03:15 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list2	*ft_lstnew_2(void *content, int i)
{
	t_list2	*new;

	if (!(new = (t_list2 *)malloc(sizeof(t_list2))))
		return (NULL);
	new->index = i;
	if (!(new->content = ft_strdup((char *)content)))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
