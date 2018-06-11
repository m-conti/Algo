/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:47:55 by mconti            #+#    #+#             */
/*   Updated: 2018/04/19 13:47:57 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_base(char *base)
{
	int i;
	int	j;

	if (!base)
		return (0);
	i = 0;
	while (base[i])
	{
		j = i;
		while (base[++j])
			if (base[i] == base[j])
				return (0);
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	return (i);
}

char				*ft_itoabase(unsigned long long nb, char *base)
{
	unsigned int		i;
	char				*str;
	unsigned int		b;

	if (!(b = ft_count_base(base)))
		return (NULL);
	i = ft_log(nb, b);
	if (!(str = ft_memalloc(i + 1)))
		return (NULL);
	while (i)
	{
		str[--i] = base[nb % b];
		nb /= b;
	}
	return (str);
}
