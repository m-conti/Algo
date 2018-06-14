/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 02:51:53 by mconti            #+#    #+#             */
/*   Updated: 2018/04/05 02:51:54 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	unsigned int i;
	unsigned int n;

	if (nb < 0)
		ft_putchar('-');
	if (nb == 0)
		ft_putchar('0');
	n = ft_abs(nb);
	i = ft_log(n, 10);
	while (i-- > 0)
	{
		ft_putchar((n / ft_power(10, i)) + 48);
		n %= ft_power(10, i);
	}
}
