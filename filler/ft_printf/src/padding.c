/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:13:28 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/09 15:53:02 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	find_prefix(char **to_w, t_conv_spec *cs)
{
	if (cs->conversion == 'X' || cs->conversion == 'x' || cs->conversion == 'p')
	{
		if (((cs->flags & HASH_FLAG) && (*to_w)[0] != '0')
				|| cs->conversion == 'p')
		{
			cs->prefix[0] = '0';
			cs->prefix[1] = (cs->conversion == 'X') ? 'X' : 'x';
		}
	}
	else if ((*to_w)[0] == '-')
	{
		cs->prefix[0] = '-';
		*to_w = &(*to_w)[1];
		cs->len--;
	}
	else if (cs->flags & PLUS_FLAG)
		cs->prefix[0] = '+';
	else if (cs->flags & SPACE_FLAG)
		cs->prefix[0] = ' ';
}

void	manage_precision(char **to_w, t_conv_spec *cs)
{
	int		ndigit;

	ndigit = cs->len;
	if ((cs->conversion == 'o' || cs->conversion == 'O')
			&& (cs->flags & HASH_FLAG))
	{
		if (cs->precision <= 1 && *to_w[0] == '0')
			cs->precision = 1;
		else
		{
			if (cs->precision < ndigit + 1)
				cs->precision = ndigit + 1;
		}
	}
	if (cs->precision == 0 && ndigit == 1 && **to_w == '0')
	{
		**to_w = '\0';
		cs->len--;
	}
	if (ndigit < cs->precision)
	{
		cs->nb_zeros_precision = cs->precision - ndigit;
	}
}

void	set_padding_spec(t_conv_spec *cs)
{
	cs->padd.size = cs->field_width -
		(cs->nb_zeros_precision + cs->len + ft_strlen(cs->prefix));
	if (cs->padd.size < 0)
		cs->padd.size = 0;
	if (cs->flags & MINUS_FLAG)
		cs->padd.position = RIGHT;
}

void	print_nb_padd_space(t_writer *w, char *to_w, t_conv_spec *cs)
{
	if (cs->flags & MINUS_FLAG)
	{
		if (cs->prefix[0])
			putstr_buf(w, cs->prefix, ft_strlen(cs->prefix));
		if (cs->nb_zeros_precision)
			put_precision_buf(w, cs);
		putstr_buf(w, to_w, cs->len);
		memset_padding_buf(w, cs);
	}
	else
	{
		memset_padding_buf(w, cs);
		if (cs->prefix[0])
			putstr_buf(w, cs->prefix, ft_strlen(cs->prefix));
		if (cs->nb_zeros_precision)
			put_precision_buf(w, cs);
		putstr_buf(w, to_w, cs->len);
	}
}

void	print_number_and_padding(t_writer *w, char *to_w, t_conv_spec *cs)
{
	cs->len = ft_strlen(to_w);
	find_prefix(&to_w, cs);
	cs->padd.filler = ((cs->flags & ZERO_FLAG) &&
			(cs->precision == UNDEFINED)
			&& (!(cs->flags & MINUS_FLAG))) ? '0' : ' ';
	manage_precision(&to_w, cs);
	set_padding_spec(cs);
	if (cs->padd.filler == '0')
	{
		if (cs->prefix[0])
			putstr_buf(w, cs->prefix, ft_strlen(cs->prefix));
		memset_padding_buf(w, cs);
		if (cs->nb_zeros_precision)
			put_precision_buf(w, cs);
		putstr_buf(w, to_w, cs->len);
	}
	else
		print_nb_padd_space(w, to_w, cs);
}
