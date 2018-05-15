/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:55:31 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/05 20:48:24 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *next_elt;
	t_list *elt;

	if (!alst)
		return ;
	elt = *alst;
	while (elt)
	{
		next_elt = elt->next;
		ft_lstdelone(&elt, del);
		elt = next_elt;
	}
	*alst = NULL;
}
