/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:19:39 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/06 17:36:42 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **alst, t_list *elt)
{
	t_list *list;

	if (!alst || !(*alst))
		*alst = elt;
	else
	{
		list = *alst;
		while (list->next)
			list = list->next;
		list->next = elt;
	}
}
