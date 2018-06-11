/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:19:34 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 17:19:35 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		dest[i] = (*f)(i, dest[i]);
		i++;
	}
	return (dest);
}
