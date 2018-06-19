/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_occ_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:22:05 by mmanley           #+#    #+#             */
/*   Updated: 2018/04/13 13:18:34 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_occ_pos(const char *str, int c)
{
	int		i;
	char	test;

	i = 0;
	test = c;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == test)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	else
		return (-1);
}
