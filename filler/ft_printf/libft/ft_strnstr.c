/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:53:06 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 15:53:08 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *str, size_t n)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (src[i] && str[j] && i < n)
	{
		j = 0;
		while (src[i + j] == str[j] && i + j < n && str[j])
			j++;
		if (str[j])
			i++;
	}
	if (!str[j])
		return ((char*)&src[i]);
	return (NULL);
}
