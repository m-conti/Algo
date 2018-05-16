/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:22:19 by mconti            #+#    #+#             */
/*   Updated: 2018/04/19 13:22:20 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
