/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:25:51 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/09 15:47:56 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conversion_o(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char	*to_w;

	if (cs->flags & HH_FLAG)
		to_w = ft_utoa_base((unsigned char)va_arg(ap, int), 8);
	else if (cs->flags & H_FLAG)
		to_w = ft_utoa_base((unsigned short)va_arg(ap, int), 8);
	else if (cs->flags & L_FLAG)
		to_w = ft_ultoa_base(va_arg(ap, unsigned long), 8);
	else if ((cs->flags & J_FLAG) || (cs->flags & Z_FLAG)
			|| (cs->flags & LL_FLAG))
		to_w = ft_umaxtoa_base(va_arg(ap, uintmax_t), 8);
	else
		to_w = ft_utoa_base(va_arg(ap, unsigned int), 8);
	cs->flags = cs->flags & (~(PLUS_FLAG | SPACE_FLAG));
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}

void	conversion_oo(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char	*to_w;

	to_w = ft_umaxtoa_base(va_arg(ap, uintmax_t), 8);
	cs->flags = cs->flags & (~(PLUS_FLAG | SPACE_FLAG));
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}

void	conversion_x(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	if (cs->flags & HH_FLAG)
		to_w = ft_strtolower(
				ft_utoa_base((unsigned char)va_arg(ap, int), 16));
	else if (cs->flags & H_FLAG)
		to_w = ft_strtolower(
				ft_utoa_base((unsigned short)va_arg(ap, int), 16));
	else if (cs->flags & L_FLAG)
		to_w = ft_strtolower(
				ft_ultoa_base(va_arg(ap, unsigned long int), 16));
	else if ((cs->flags & LL_FLAG) || (cs->flags & J_FLAG) ||
			(cs->flags & Z_FLAG))
		to_w = ft_strtolower(ft_umaxtoa_base(va_arg(ap, uintmax_t), 16));
	else
		to_w = ft_strtolower(ft_utoa_base(va_arg(ap, unsigned int), 16));
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}

void	conversion_xx(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	if (cs->flags & HH_FLAG)
		to_w = ft_utoa_base((unsigned char)va_arg(ap, int), 16);
	else if (cs->flags & H_FLAG)
		to_w = ft_utoa_base((unsigned short)va_arg(ap, int), 16);
	else if (cs->flags & L_FLAG)
		to_w = ft_ultoa_base(va_arg(ap, unsigned long int), 16);
	else if ((cs->flags & LL_FLAG) || (cs->flags & J_FLAG)
			|| (cs->flags & Z_FLAG))
		to_w = ft_umaxtoa_base(va_arg(ap, uintmax_t), 16);
	else
		to_w = ft_utoa_base(va_arg(ap, unsigned int), 16);
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}

void	conversion_b(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	to_w = ft_umaxtoa_base(va_arg(ap, uintmax_t), 2);
	if (!to_w)
	{
		cs->error = MALLOC_ERROR;
		return ;
	}
	print_number_and_padding(w, to_w, cs);
	free(to_w);
}
