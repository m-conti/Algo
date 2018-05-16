/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 16:46:34 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/19 10:44:04 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	dst_ptr = (unsigned char*)dst;
	src_ptr = (const unsigned char*)src;
	if (src < dst)
		while (len--)
			*(dst_ptr + len) = *(src_ptr + len);
	else
		while (len--)
			*dst_ptr++ = *src_ptr++;
	return (dst);
}
