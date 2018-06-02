/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:32:06 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/02 15:05:09 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int opt)
{
	char *dest;

	dest = ft_strjoin(s1, s2);
	if (s1 && (opt & 1))
		free(s1);
	if (s2 && (opt & 2))
		free(s2);
	return (dest);
}
