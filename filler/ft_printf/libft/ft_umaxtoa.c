/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_umaxtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:38:07 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/08 15:07:56 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_umaxtoa(uintmax_t n)
{
	uintmax_t		nn;
	unsigned int	nb_char;
	char			*ret;

	nb_char = 0;
	nn = n;
	while (nn > 0)
	{
		nn = nn / 10;
		nb_char++;
	}
	nb_char = (n == 0) ? 1 : nb_char;
	if (!(ret = malloc(sizeof(char) * (nb_char + 1))))
		return (NULL);
	ret[nb_char] = '\0';
	nn = n;
	while (nn > 0)
	{
		ret[nb_char - 1] = nn % 10 + '0';
		nn = nn / 10;
		nb_char--;
	}
	ret[0] = (n == 0) ? '0' : ret[0];
	return (ret);
}
