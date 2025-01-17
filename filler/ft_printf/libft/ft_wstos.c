/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 23:13:33 by mconti            #+#    #+#             */
/*   Updated: 2018/05/08 23:13:34 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wstos(wchar_t *src, char *dest)
{
	int i;
	int r;

	i = 0;
	r = 0;
	if (!src)
		return (0);
	while (src[i])
		r += ft_wctos(src[i++], &dest[r]);
	dest[r] = 0;
	return (r);
}
