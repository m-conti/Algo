/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countsep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:56:04 by mconti            #+#    #+#             */
/*   Updated: 2018/04/05 01:56:05 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_countsep(char const *s, char c)
{
	int				split;
	int				i;
	unsigned int	y;

	i = 0;
	y = 0;
	while (s[i])
	{
		split = ft_index(&s[i], c);
		if (split > 0)
		{
			i += split;
			if (s[i])
				y++;
		}
		i++;
	}
	if (i > 0 && y > 0 && s[i - 1] == c)
		y--;
	return (y);
}
