/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:28:29 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/09 15:28:49 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_bits(unsigned int octet, int size)
{
	int oct;

	oct = octet;
	if (size)
	{
		ft_print_bits(octet >> 1, size - 1);
		ft_putchar('0' + (oct & 1));
		if (size % 8 == 0)
			ft_putchar(' ');
	}
}
