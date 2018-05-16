/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 12:50:31 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 12:50:32 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char*)src;
	s2 = (unsigned char*)dest;
	if (n == 0)
		return (dest);
	if (s1 < s2)
	{
		i = n;
		while (--i > 0)
			s2[i] = s1[i];
		s2[i] = s1[i];
	}
	else if (s1 > s2)
	{
		i = 0;
		while (i < n)
		{
			s2[i] = s1[i];
			i++;
		}
	}
	return (dest);
}
