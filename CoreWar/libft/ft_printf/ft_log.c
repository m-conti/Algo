/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:22:19 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 20:14:42 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_log(unsigned long long nb, unsigned int const base)
{
	unsigned int	log;

	log = 0;
	if (!nb)
		return (1);
	while (nb)
	{
		nb /= base;
		log++;
	}
	return (log);
}
