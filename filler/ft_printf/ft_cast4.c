/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 01:13:40 by mconti            #+#    #+#             */
/*   Updated: 2018/05/09 01:13:42 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_cast_c(va_list *ap)
{
	intmax_t i;

	i = (char)va_arg(*ap, int);
	return (i);
}

intmax_t	ft_cast_wc(va_list *ap)
{
	return (va_arg(*ap, wchar_t));
}

intmax_t	ft_cast_s(va_list *ap)
{
	return ((intmax_t)va_arg(*ap, char*));
}

intmax_t	ft_cast_ws(va_list *ap)
{
	return ((intmax_t)va_arg(*ap, wchar_t*));
}
