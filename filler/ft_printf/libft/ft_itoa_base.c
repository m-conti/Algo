/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:45:34 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/24 16:38:55 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			get_base_char(int n)
{
	if (n < 10)
		return ('0' + n);
	else
		return (n + 'A' - 10);
}

static unsigned int	nchar_base(int value, unsigned int base)
{
	unsigned int	n;
	unsigned int	nchar;

	if (base == 10)
	{
		nchar = (value < 0) ? 2 : 1;
		n = (value < 0) ? -value : value;
	}
	else
	{
		nchar = 1;
		n = (value < 0) ? -value : value;
	}
	while (n >= base)
	{
		n = n / base;
		nchar++;
	}
	return (nchar);
}

char				*ft_itoa_base(int value, unsigned int base)
{
	unsigned int	nchar;
	char			*ret;
	int				i;
	unsigned int	n;

	if (base < 2 || base > 16)
		return (NULL);
	nchar = nchar_base(value, base);
	if (!(ret = ft_strnew(nchar)))
		return (0);
	ret[nchar] = '\0';
	if (value == 0)
		ret[0] = '0';
	if (base == 10 && value < 0)
		ret[0] = '-';
	i = 1;
	n = (value < 0) ? -value : value;
	while (n > 0)
	{
		ret[nchar - i++] = get_base_char(n % base);
		n = n / base;
	}
	return (ret);
}
