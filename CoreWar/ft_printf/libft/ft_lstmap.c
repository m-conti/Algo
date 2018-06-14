/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:51:29 by mconti            #+#    #+#             */
/*   Updated: 2018/04/06 18:51:32 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	debut;
	t_list	*new;

	debut.next = NULL;
	while (lst)
	{
		if (!(new = (*f)(lst)))
			return (NULL);
		ft_lstradd(&debut, new);
		lst = lst->next;
	}
	return (debut.next);
}
