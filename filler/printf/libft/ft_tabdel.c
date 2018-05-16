/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 23:53:49 by mconti            #+#    #+#             */
/*   Updated: 2018/04/09 23:53:51 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_tabdel(void **tab, unsigned int y)
{
	unsigned int i;

	i = 0;
	while (i < y)
		free(tab[i++]);
	free(*tab);
	return (NULL);
}
