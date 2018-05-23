/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 15:44:25 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/09 14:29:33 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_and_empty_buf(t_writer *w)
{
	w->len += w->buf_i;
	write(1, &(w->buf[0]), w->buf_i);
	w->buf_i = 0;
	ft_bzero(w->buf, BUFF_SIZE);
}

void	putchar_buf(t_writer *w, char c)
{
	w->buf[w->buf_i] = c;
	w->buf_i++;
	if (w->buf_i > BUFF_SIZE - 1)
		print_and_empty_buf(w);
}

void	put_precision_buf(t_writer *w, t_conv_spec *cs)
{
	int		len_mm;
	int		len_to_write;

	len_to_write = cs->nb_zeros_precision;
	if (len_to_write > 0)
	{
		if (w->buf_i + len_to_write > BUFF_SIZE - 1)
		{
			while ((w->buf_i + len_to_write) > BUFF_SIZE - 1)
			{
				len_mm = BUFF_SIZE - 1 - w->buf_i;
				ft_memset(&w->buf[w->buf_i], '0', len_mm);
				w->buf_i += len_mm;
				len_to_write -= (len_mm);
				print_and_empty_buf(w);
			}
			ft_memset(&w->buf[w->buf_i], '0', len_to_write);
			w->buf_i += len_to_write;
		}
		else
		{
			ft_memset(&w->buf[w->buf_i], '0', len_to_write);
			w->buf_i += len_to_write;
		}
	}
}

void	memset_padding_buf(t_writer *w, t_conv_spec *cs)
{
	int		len_mm;
	int		len_to_write;

	len_to_write = cs->padd.size;
	if (len_to_write > 0)
	{
		if (w->buf_i + len_to_write > BUFF_SIZE - 1)
		{
			while ((w->buf_i + len_to_write) > BUFF_SIZE - 1)
			{
				len_mm = BUFF_SIZE - 1 - w->buf_i;
				ft_memset(&w->buf[w->buf_i], cs->padd.filler, len_mm);
				w->buf_i += len_mm;
				len_to_write -= (len_mm);
				print_and_empty_buf(w);
			}
			ft_memset(&w->buf[w->buf_i], cs->padd.filler, len_to_write);
			w->buf_i += len_to_write;
		}
		else
		{
			ft_memset(&w->buf[w->buf_i], cs->padd.filler, len_to_write);
			w->buf_i += len_to_write;
		}
	}
}

void	putstr_buf(t_writer *w, char *s, int len)
{
	int		i_s;
	int		len_mm;

	i_s = 0;
	if (w->buf_i + len > BUFF_SIZE - 1)
	{
		while (w->buf_i + (len - i_s) > BUFF_SIZE - 1)
		{
			len_mm = BUFF_SIZE - 1 - w->buf_i;
			ft_memmove(&w->buf[w->buf_i], &s[i_s], len_mm);
			w->buf_i += len_mm;
			i_s += (len_mm);
			print_and_empty_buf(w);
		}
		len_mm = len - i_s;
		ft_memmove(&w->buf[w->buf_i], &s[i_s], len_mm);
		w->buf_i += len_mm;
	}
	else
	{
		ft_memmove(&w->buf[w->buf_i], s, len);
		w->buf_i += len;
	}
}
