/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 13:16:29 by mconti            #+#    #+#             */
/*   Updated: 2018/04/22 17:59:20 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char*)s;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && str[i] != (unsigned char)c)
		i++;
	if (str[i] == (unsigned char)c)
		return ((void*)&s[i]);
	return (NULL);
}
