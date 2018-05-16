/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:28:29 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/03 17:31:17 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
			&& (s1[i] != '\0') && (i < n))
		i++;
	if (i == n)
		i--;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}
