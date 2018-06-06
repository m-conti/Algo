/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 02:58:26 by mconti            #+#    #+#             */
/*   Updated: 2018/04/05 02:58:27 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int i;
	unsigned int n;

	if (nb < 0)
		ft_putchar_fd('-', fd);
	if (nb == 0)
		ft_putchar_fd('0', fd);
	n = ft_abs(nb);
	i = ft_log(n, 10);
	while (i-- > 0)
	{
		ft_putchar_fd((n / ft_power(10, i)) + 48, fd);
		n %= ft_power(10, i);
	}
}
