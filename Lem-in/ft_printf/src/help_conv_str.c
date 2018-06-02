/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_conv_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 19:09:07 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/09 16:55:48 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*nullify(void)
{
	char *ret;

	ret = ft_strnew(7);
	ft_strcpy(ret, "(null)");
	return (ret);
}

void	putbuf_and_free(t_writer *w, char *to_w, t_conv_spec *cs)
{
	if (cs->padd.position == LEFT)
		memset_padding_buf(w, cs);
	putstr_buf(w, to_w, cs->len);
	if (cs->padd.position == RIGHT)
		memset_padding_buf(w, cs);
	if (to_w)
		free(to_w);
}

char	*conv_s_build_to_w(t_conv_spec *cs, va_list ap)
{
	char *rec;
	char *ret;

	rec = va_arg(ap, char *);
	if (rec == NULL)
	{
		if (!(ret = nullify()))
		{
			cs->error = MALLOC_ERROR;
			return (NULL);
		}
	}
	else
	{
		if (!(ret = ft_strnew(ft_strlen(rec))))
		{
			cs->error = MALLOC_ERROR;
			return (NULL);
		}
		ft_strcpy(ret, rec);
	}
	return (ret);
}

char	*conv_ss_build_to_w(t_conv_spec *cs, va_list ap)
{
	int		i_to_w;
	wchar_t	*rec;
	char	*ret;

	rec = va_arg(ap, wchar_t *);
	if (rec == NULL)
	{
		if (!(ret = nullify()))
			return (NULL);
		cs->len = ft_strlen(ret);
		return (ret);
	}
	i_to_w = 0;
	if (!(ret = ft_strnew(sizeof(rec) * 4)))
		return (NULL);
	while (*rec)
		if (!(putwchar_str(ret, *rec++, &i_to_w, cs)))
			break ;
	cs->len = i_to_w;
	return (ret);
}
