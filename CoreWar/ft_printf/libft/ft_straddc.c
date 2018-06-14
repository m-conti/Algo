/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:05:08 by mconti            #+#    #+#             */
/*   Updated: 2018/04/25 15:05:09 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddc(char *str, char c, size_t nb)
{
	char	*dest;
	int		i;

	i = ft_strlen(str);
	if (!(dest = (char*)ft_memalloc(i + nb + 1)))
		return (str);
	dest = ft_strcpy(dest, str);
	dest = ft_memset(&dest[i], c, nb);
	free(str);
	return (dest);
}
