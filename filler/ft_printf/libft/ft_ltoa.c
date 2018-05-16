/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:04:38 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/01 19:01:51 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(long n)
{
	unsigned long int	nn;
	unsigned int		nb_char;
	char				*ret;

	nn = (n < 0) ? -n : n;
	nb_char = (n < 0) ? 1 : 0;
	while (nn > 0)
	{
		nn = nn / 10;
		nb_char++;
	}
	nb_char = (n == 0) ? 1 : nb_char;
	if (!(ret = malloc(sizeof(char) * (nb_char + 1))))
		return (NULL);
	ret[nb_char] = '\0';
	nn = (n < 0) ? -n : n;
	while (nn > 0)
	{
		ret[nb_char - 1] = nn % 10 + '0';
		nn = nn / 10;
		nb_char--;
	}
	ret[0] = (nb_char == 1) ? '-' : ret[0];
	ret[0] = (n == 0) ? '0' : ret[0];
	return (ret);
}
