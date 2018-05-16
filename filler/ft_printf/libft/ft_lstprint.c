/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:29:59 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/11 17:44:30 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	int c;

	c = 0;
	if (!lst)
		return ;
	while (lst)
	{
		ft_lstcont(lst);
		ft_putchar('\n');
		lst = lst->next;
		c++;
	}
}
