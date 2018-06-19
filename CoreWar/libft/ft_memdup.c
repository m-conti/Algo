/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 06:55:10 by mconti            #+#    #+#             */
/*   Updated: 2018/04/06 06:55:12 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void const *src, size_t len)
{
	void	*dest;

	if (!(dest = malloc(len)))
		return (NULL);
	return (ft_memcpy(dest, src, len));
}
