/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 12:48:05 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 12:48:06 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s2 = (unsigned char*)dest;
	s1 = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		s2[i] = s1[i];
		if (s1[i] == (unsigned char)c)
			return (&dest[i + 1]);
		i++;
	}
	return (NULL);
}
