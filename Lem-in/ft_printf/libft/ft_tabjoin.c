/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:43:19 by mconti            #+#    #+#             */
/*   Updated: 2018/05/30 11:43:20 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tabjoin(char **tab, int n)
{
	int		i;
	char	*dest;

	i = -1;
	dest = NULL;
	while (++i < n)
		if (!(dest = ft_strjoinfree(dest, tab[i], 1)))
			return (NULL);
	return (dest);
}
