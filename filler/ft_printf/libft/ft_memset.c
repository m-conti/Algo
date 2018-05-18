/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 16:32:23 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/03 16:34:11 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	to_put;
	unsigned char	*ptr_pos;

	to_put = (unsigned char)c;
	ptr_pos = (unsigned char *)b;
	while (len--)
		*ptr_pos++ = to_put;
	return (b);
}
