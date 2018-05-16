/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:29:53 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/05 19:03:32 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *elem;

	elem = malloc(sizeof(t_list));
	if (elem)
	{
		if (content == NULL)
		{
			elem->content = NULL;
			elem->content_size = 0;
		}
		else
		{
			if (!(elem->content = ft_memalloc(content_size)))
				return (NULL);
			ft_memcpy(elem->content, content, content_size);
			elem->content_size = content_size;
		}
		elem->next = NULL;
	}
	return (elem);
}
