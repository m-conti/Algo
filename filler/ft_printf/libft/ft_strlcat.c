/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:34:49 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 15:34:50 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;

	i = 0;
	j = 0;
	while (i < size && dest[i])
		i++;
	if (i == size)
	{
		while (src[j])
			j++;
		return (size + j);
	}
	while (i < size - 1 && src[j])
		dest[i++] = src[j++];
	dest[i] = 0;
	n = i - j;
	while (src[j])
		j++;
	return (j + n);
}
