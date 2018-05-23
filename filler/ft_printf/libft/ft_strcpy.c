/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:06:12 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 15:06:13 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
