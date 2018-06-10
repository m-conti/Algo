/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:24:22 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/06 14:38:26 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	char	*cp_h;

	if (*needle == '\0')
		return (char*)haystack;
	cp_h = (char*)haystack;
	i = 0;
	while (cp_h[i])
	{
		j = 0;
		while (cp_h[i + j] == needle[j] && cp_h[i + j] != '\0')
			j++;
		if (needle[j] == '\0')
			return (&cp_h[i]);
		i++;
	}
	return (NULL);
}
