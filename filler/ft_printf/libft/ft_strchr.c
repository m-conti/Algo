/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:17:52 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/03 17:22:27 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char cc;
	char *ret;

	cc = (char)c;
	ret = NULL;
	while (*s && !ret)
	{
		if (*s == cc)
			ret = (char*)s;
		s++;
	}
	if (*s == '\0' && cc == '\0')
		ret = (char*)s;
	return (ret);
}
