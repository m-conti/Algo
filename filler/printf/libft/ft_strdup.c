/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:44:54 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 14:44:55 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	unsigned int	i;
	char			*dest;

	if (!(dest = (char*)ft_memalloc(ft_strlen((char*)src) + 1)))
		return (NULL);
	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
