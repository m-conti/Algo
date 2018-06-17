/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:05:15 by mconti            #+#    #+#             */
/*   Updated: 2018/04/25 15:05:17 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcadd(char *str, char c, size_t nb)
{
	char *dest;

	if (!(dest = (char*)ft_memalloc(ft_strlen(str) + nb + 1)))
		return (str);
	dest = ft_memset(dest, c, nb);
	dest = ft_strcat(dest, str);
	free(str);
	return (dest);
}
