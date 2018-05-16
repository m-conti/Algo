/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:17:39 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/10 10:42:28 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conversion_c(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char to_w;

	if (cs->flags & L_FLAG)
		conversion_cc(w, cs, ap);
	else
	{
		to_w = (char)va_arg(ap, int);
		cs->len = 1;
		cs->padd.filler = (cs->flags & ZERO_FLAG &&
				!(cs->flags & MINUS_FLAG)) ? '0' : ' ';
		set_padding_spec(cs);
		if (cs->padd.position == LEFT)
			memset_padding_buf(w, cs);
		putchar_buf(w, to_w);
		if (cs->padd.position == RIGHT)
			memset_padding_buf(w, cs);
	}
}

char	*conv_cc_build_to_w(t_conv_spec *cs, va_list ap)
{
	wchar_t	rec;
	char	*ret;
	int		i_ret;

	rec = (wchar_t)va_arg(ap, wint_t);
	if (rec)
	{
		if (!(ret = ft_strnew(5)))
			return (NULL);
		i_ret = 0;
		if (!(putwchar_str(ret, rec, &i_ret, cs)))
		{
			cs->error = INVALID_CHAR_ERROR;
			return (NULL);
		}
		cs->len = i_ret;
	}
	else
	{
		if (!(ret = ft_strnew(1)))
			return (NULL);
		ret[0] = '\0';
		cs->len = 1;
	}
	return (ret);
}

void	conversion_cc(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char	*to_w;

	to_w = conv_cc_build_to_w(cs, ap);
	if (to_w == NULL)
	{
		if (!(cs->error))
			cs->error = MALLOC_ERROR;
		return ;
	}
	cs->padd.filler = (cs->flags & ZERO_FLAG &&
			!(cs->flags & MINUS_FLAG)) ? '0' : ' ';
	set_padding_spec(cs);
	putbuf_and_free(w, to_w, cs);
}

void	conversion_s(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char *to_w;

	if (cs->flags & L_FLAG)
		conversion_ss(w, cs, ap);
	else
	{
		to_w = conv_s_build_to_w(cs, ap);
		if (to_w == NULL)
			return ;
		cs->len = ft_strlen(to_w);
		if (cs->precision != UNDEFINED && (cs->len > cs->precision))
			cs->len = cs->precision;
		cs->padd.filler = (cs->flags & ZERO_FLAG &&
				!(cs->flags & MINUS_FLAG)) ? '0' : ' ';
		set_padding_spec(cs);
		putbuf_and_free(w, to_w, cs);
	}
}

void	conversion_ss(t_writer *w, t_conv_spec *cs, va_list ap)
{
	char	*to_w;

	to_w = conv_ss_build_to_w(cs, ap);
	if (to_w == NULL)
	{
		if (!(cs->error))
			cs->error = MALLOC_ERROR;
		return ;
	}
	if (cs->precision != UNDEFINED && (cs->len > cs->precision))
		cs->len = cs->precision;
	cs->padd.filler = (cs->flags & ZERO_FLAG &&
			!(cs->flags & MINUS_FLAG)) ? '0' : ' ';
	set_padding_spec(cs);
	putbuf_and_free(w, to_w, cs);
}
