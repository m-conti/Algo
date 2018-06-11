/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wsntos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 20:58:32 by mconti            #+#    #+#             */
/*   Updated: 2018/05/12 20:58:36 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wsntos(wchar_t *src, char *dest, size_t n)
{
	size_t	i;
	int		r;

	i = 0;
	r = 0;
	if (!src)
		return (0);
	while (src[i] && i < n)
		r += ft_wctos(src[i++], &dest[r]);
	dest[i] = 0;
	return (i);
}
