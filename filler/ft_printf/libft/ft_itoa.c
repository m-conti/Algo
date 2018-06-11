/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:02:25 by mconti            #+#    #+#             */
/*   Updated: 2018/04/19 13:02:27 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long nbr)
{
	unsigned long long	nb;
	unsigned int		i;
	char				*str;

	nb = nbr >= 0 ? nbr : -nbr;
	i = 0;
	if (nbr < 0)
		i++;
	i += ft_log(nb, 10);
	if (!(str = ft_memalloc(i + 1)))
		return (NULL);
	while (i)
	{
		str[--i] = nb % 10 + '0';
		nb /= 10;
	}
	if (nbr < 0)
		str[0] = '-';
	return (str);
}
