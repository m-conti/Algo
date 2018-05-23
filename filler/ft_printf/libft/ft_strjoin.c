/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:40:21 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 17:40:22 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	l1;
	unsigned int	len;
	char			*dest;

	l1 = ft_strlen(s1);
	len = l1 + ft_strlen(s2);
	if (!(dest = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strcpy(dest, s1);
	ft_strcpy(dest + l1, s2);
	return (dest);
}
