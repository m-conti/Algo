/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 21:26:07 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/06 16:03:05 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **alst)
{
	t_list	*next;
	t_list	*previous;
	t_list	*cur;
	int		first;

	if (!(*alst))
		return ;
	first = 1;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		if (first)
		{
			cur->next = NULL;
			first = 0;
		}
		else
			cur->next = previous;
		previous = cur;
		cur = next;
	}
	*alst = previous;
}
