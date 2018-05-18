/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:02:33 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/16 20:18:39 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(void **tab, int y)
{
	int i;

	i = 0;
	if (!tab || !tab[i])
		return ;
	if (y == -1)
	{
		while (tab[i] != NULL)
			free(tab[i++]);
	}
	else
		while (i < y)
			free(tab[i++]);
	free(*tab);
}
