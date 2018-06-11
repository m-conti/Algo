/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:44:54 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 15:44:55 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *src, const char *str)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (src[i] && str[j])
	{
		j = 0;
		while (src[i + j] == str[j] && str[j])
			j++;
		if (str[j])
			i++;
	}
	if (!str[j])
		return ((char*)&src[i]);
	return (NULL);
}
