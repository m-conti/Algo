/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:31:29 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/10 10:44:12 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*init_writer(t_writer *w)
{
	ft_bzero(w->buf, BUFF_SIZE);
	w->buf_i = 0;
	w->len = 0;
	return (w);
}

void	init_conv_spec(t_conv_spec *cs)
{
	cs->flags = 0;
	ft_bzero(cs->prefix, 3);
	cs->conversion = '\0';
	cs->field_width = UNDEFINED;
	cs->precision = UNDEFINED;
	cs->len = UNDEFINED;
	cs->nb_zeros_precision = 0;
	cs->error = 0;
	cs->padd.size = 0;
	cs->padd.filler = UNDEFINED;
	cs->padd.position = LEFT;
}

int		apply_conversion(t_writer *writer, t_conv_spec *cs, va_list ap,
		void (*conversion[128])(t_writer*, t_conv_spec*, va_list))
{
	if (ft_strchr(CONVERSIONS, cs->conversion))
		conversion[(int)cs->conversion](writer, cs, ap);
	else
	{
		cs->len = 1;
		cs->padd.filler = (cs->flags & ZERO_FLAG &&
				!(cs->flags & MINUS_FLAG)) ? '0' : ' ';
		set_padding_spec(cs);
		if (cs->padd.position == LEFT)
			memset_padding_buf(writer, cs);
		putchar_buf(writer, cs->conversion);
		if (cs->padd.position == RIGHT)
			memset_padding_buf(writer, cs);
	}
	return (1);
}

int		last_write_and_return(t_writer *w)
{
	if (w->buf_i > 0)
		print_and_empty_buf(w);
	return (w->len);
}

int		ft_printf(const char *format, ...)
{
	t_writer	writer;
	t_conv_spec	cs;
	void		(*conversion[128]) (t_writer*, t_conv_spec*, va_list);
	va_list		ap;

	va_start(ap, format);
	build_tab_conv(conversion);
	init_writer(&writer);
	while (*format)
	{
		if (*format == '%')
		{
			if (!(*(format + 1)))
				break ;
			format += build_conv_spec(&cs, (char*)(format + 1));
			apply_conversion(&writer, &cs, ap, conversion);
			if (cs.error)
				return (-1);
		}
		else
			putchar_buf(&writer, *format);
		format++;
	}
	va_end(ap);
	return (last_write_and_return(&writer));
}
