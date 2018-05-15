/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:04:27 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/02 18:04:39 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			get_base_char(unsigned int n)
{
	if (n < 10)
		return ('0' + n);
	else
		return (n + 'A' - 10);
}

static unsigned int	nchar_base(unsigned int value, unsigned int base)
{
	unsigned int	nchar;

	nchar = 1;
	while (value >= base)
	{
		value = value / base;
		nchar++;
	}
	return (nchar);
}

char				*ft_utoa_base(unsigned int value, unsigned int base)
{
	unsigned int	nchar;
	char			*ret;
	int				i;

	if (base < 2 || base > 16)
		return (NULL);
	nchar = nchar_base(value, base);
	if (!(ret = ft_strnew(nchar)))
		return (0);
	ret[nchar] = '\0';
	if (value == 0)
		ret[0] = '0';
	i = 1;
	while (value > 0)
	{
		ret[nchar - i++] = get_base_char(value % base);
		value = value / base;
	}
	return (ret);
}
