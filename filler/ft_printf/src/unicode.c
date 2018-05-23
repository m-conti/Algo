/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:27:32 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/10 10:52:06 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_strong_bit(unsigned int val)
{
	int c;

	if (val > MAX_UNICODE_VAL)
		return (0);
	c = 0;
	while (val)
	{
		val >>= 1;
		c++;
	}
	return (c);
}

int	four_bytes(char *to_w, wchar_t c, int *i_to_w, int max_i_to_w)
{
	if (*i_to_w + 3 >= max_i_to_w)
		return (0);
	to_w[*i_to_w + 3] = LEFT_BIT | (SIX_RIGHTEST_BITS & c);
	c >>= 6;
	to_w[*i_to_w + 2] = LEFT_BIT | (SIX_RIGHTEST_BITS & c);
	c >>= 6;
	to_w[*i_to_w + 1] = LEFT_BIT | (SIX_RIGHTEST_BITS & c);
	c >>= 6;
	to_w[*i_to_w] = FOUR_LEFTEST_BITS | (THREE_RIGHTEST_BITS & c);
	*i_to_w += 4;
	return (1);
}

int	three_bytes(char *to_w, wchar_t c, int *i_to_w, int max_i_to_w)
{
	if (*i_to_w + 2 >= max_i_to_w)
		return (0);
	to_w[*i_to_w + 2] = LEFT_BIT | (SIX_RIGHTEST_BITS & c);
	c >>= 6;
	to_w[*i_to_w + 1] = LEFT_BIT | (SIX_RIGHTEST_BITS & c);
	c >>= 6;
	to_w[*i_to_w] = THREE_LEFTEST_BITS | (FOUR_RIGHTEST_BITS & c);
	*i_to_w += 3;
	return (1);
}

int	two_bytes(char *to_w, wchar_t c, int *i_to_w, int max_i_to_w)
{
	if (*i_to_w + 1 >= max_i_to_w)
		return (0);
	to_w[*i_to_w + 1] = LEFT_BIT | (SIX_RIGHTEST_BITS & c);
	c = c >> 6;
	to_w[*i_to_w] = TWO_LEFTEST_BITS | (FIVE_RIGHTEST_BITS & c);
	*i_to_w += 2;
	return (1);
}

int	putwchar_str(char *to_w, wchar_t c, int *i_to_w, t_conv_spec *cs)
{
	int		nb_bits;
	int		max_i_to_w;

	if (cs->precision != UNDEFINED)
		max_i_to_w = cs->precision;
	else
		max_i_to_w = INT_MAX;
	nb_bits = check_strong_bit(c);
	if (nb_bits == -1)
		return (0);
	if (nb_bits <= 7)
	{
		if (*i_to_w >= max_i_to_w)
			return (0);
		to_w[*i_to_w] = c;
		*i_to_w += 1;
		return (1);
	}
	else if (nb_bits <= 11)
		return (two_bytes(to_w, c, i_to_w, max_i_to_w));
	else if (nb_bits <= 16)
		return (three_bytes(to_w, c, i_to_w, max_i_to_w));
	else if (nb_bits <= 21)
		return (four_bytes(to_w, c, i_to_w, max_i_to_w));
	return (0);
}
