/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 17:36:39 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/10 10:45:34 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conversion_p(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	to_w = ft_strtolower(ft_lltoa_base(
				(unsigned long long)va_arg(ap, void*), 16));
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}

void	conversion_perc(t_writer *w, t_conv_spec *cs, va_list ap)
{
	(void)ap;
	if (cs->flags & SPACE_FLAG)
		cs->flags -= SPACE_FLAG;
	if (cs->precision != UNDEFINED)
		cs->precision = UNDEFINED;
	print_number_and_padding(w, "%", cs);
}

void	build_tab_conv(void (*conversion[128])
		(t_writer*, t_conv_spec*, va_list))
{
	conversion['s'] = &conversion_s;
	conversion['S'] = &conversion_ss;
	conversion['p'] = &conversion_p;
	conversion['d'] = &conversion_d_i;
	conversion['D'] = &conversion_dd;
	conversion['i'] = &conversion_d_i;
	conversion['o'] = &conversion_o;
	conversion['O'] = &conversion_oo;
	conversion['u'] = &conversion_u;
	conversion['U'] = &conversion_uu;
	conversion['x'] = &conversion_x;
	conversion['X'] = &conversion_xx;
	conversion['c'] = &conversion_c;
	conversion['C'] = &conversion_cc;
	conversion['b'] = &conversion_b;
	conversion['%'] = &conversion_perc;
}
