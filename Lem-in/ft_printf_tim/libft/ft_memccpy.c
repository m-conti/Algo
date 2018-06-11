/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 16:40:28 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/05 10:19:28 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		c_uc;
	unsigned char		*dst_ptr;
	unsigned char		*ret;
	const unsigned char	*src_ptr;

	ret = NULL;
	c_uc = (unsigned char)c;
	dst_ptr = (unsigned char*)dst;
	src_ptr = (unsigned char*)src;
	while (n-- && !(ret))
	{
		if (*src_ptr == (unsigned char)c)
			ret = (unsigned char *)(dst_ptr + 1);
		*dst_ptr++ = *src_ptr++;
	}
	return (ret);
}
