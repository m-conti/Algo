/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:29:02 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/11 17:56:05 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstcont(t_list *elt)
{
	size_t	i;
	char	*content_ptr;

	i = 0;
	if (!elt)
		ft_putstr("(null)");
	else
	{
		content_ptr = (char *)elt->content;
		while (i < elt->content_size)
		{
			ft_putchar(content_ptr[i]);
			i++;
		}
	}
}
