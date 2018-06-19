/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_nbr_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:39:06 by mmanley           #+#    #+#             */
/*   Updated: 2018/01/10 15:42:24 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		rec_nbr_count(long nb, int i, int base)
{
	if (nb < 0)
	{
		if (base == 10)
			i++;
		nb *= -1;
	}
	if (nb >= base)
		return (rec_nbr_count(nb / base, i + 1, base));
	return (i);
}
