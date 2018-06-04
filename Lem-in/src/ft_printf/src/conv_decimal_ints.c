/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_decimal_ints.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 16:17:58 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/09 15:46:59 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conversion_d_i(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	if (cs->flags & L_FLAG)
		to_w = ft_ltoa(va_arg(ap, long));
	else if (cs->flags & LL_FLAG)
		to_w = ft_lltoa(va_arg(ap, long long));
	else if (cs->flags & H_FLAG)
		to_w = ft_itoa((short)va_arg(ap, int));
	else if (cs->flags & HH_FLAG)
		to_w = ft_itoa((signed char)va_arg(ap, int));
	else if (cs->flags & J_FLAG || cs->flags & Z_FLAG)
		to_w = ft_imaxtoa(va_arg(ap, intmax_t));
	else
		to_w = ft_itoa(va_arg(ap, int));
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}

void	conversion_dd(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	to_w = ft_ltoa(va_arg(ap, long));
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}

void	conversion_u(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	if (cs->flags & PLUS_FLAG)
		cs->flags -= PLUS_FLAG;
	if (cs->flags & HH_FLAG)
		to_w = ft_itoa((unsigned char)va_arg(ap, int));
	else if (cs->flags & H_FLAG)
		to_w = ft_itoa((unsigned short)va_arg(ap, int));
	else if (cs->flags & L_FLAG)
		to_w = ft_ultoa(va_arg(ap, unsigned long));
	else if ((cs->flags & J_FLAG) || (cs->flags & Z_FLAG)
			|| (cs->flags & LL_FLAG))
		to_w = ft_umaxtoa(va_arg(ap, uintmax_t));
	else
		to_w = ft_utoa(va_arg(ap, unsigned int));
	if (cs->flags & SPACE_FLAG)
		cs->flags = cs->flags - SPACE_FLAG;
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}

void	conversion_uu(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	if (cs->flags & PLUS_FLAG)
		cs->flags -= PLUS_FLAG;
	to_w = ft_ultoa(va_arg(ap, unsigned long));
	if (cs->flags & SPACE_FLAG)
		cs->flags = cs->flags - SPACE_FLAG;
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}
