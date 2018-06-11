/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:23:00 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/03 17:23:23 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char cc;
	char *latest_c;

	cc = (char)c;
	latest_c = NULL;
	while (*s)
	{
		if (*s == cc)
			latest_c = (char*)s;
		s++;
	}
	if (*s == '\0' && cc == '\0')
		latest_c = (char*)s;
	return (latest_c);
}
