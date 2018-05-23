/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:06:07 by mconti            #+#    #+#             */
/*   Updated: 2018/04/06 18:06:08 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	while (*alst)
	{
		tmp = (*alst)->next;
		ft_lstdelone(alst, del);
		(*alst) = tmp;
	}
}
