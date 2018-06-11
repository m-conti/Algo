/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:13:47 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 17:13:49 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*dest;

	if (!s || !f)
		return (NULL);
	if (!(dest = ft_strdup(s)))
		return (NULL);
	i = 0;
	while (dest[i])
	{
		dest[i] = (*f)(dest[i]);
		i++;
	}
	return (dest);
}
