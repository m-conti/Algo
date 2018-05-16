/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:10:19 by mconti            #+#    #+#             */
/*   Updated: 2018/04/26 15:13:21 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwchar(wchar_t c)
{
	int len;

	len = 1;
	while (c >> len)
		len++;
	if (len <= 7)
		write(1, &c, 1);
	else if (len <= 11)
	{
		ft_putchar(((c >> 6) & 31) | 196);
		ft_putchar((c & 63) | 128);
	}
	else if (len <= 16)
	{
		ft_putchar(((c >> 12) & 15) | 224);
		ft_putchar(((c >> 6) & 63) | 128);
		ft_putchar((c & 63) | 128);
	}
	else
	{
		ft_putchar(((c >> 18) & 7) | 240);
		ft_putchar(((c >> 12) & 63) | 128);
		ft_putchar(((c >> 6) & 63) | 128);
		ft_putchar((c & 63) | 128);
	}
}
