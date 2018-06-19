/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 01:13:15 by mconti            #+#    #+#             */
/*   Updated: 2018/05/09 01:13:17 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_cast_si(va_list *ap)
{
	return (va_arg(*ap, int));
}

intmax_t	ft_cast_sh(va_list *ap)
{
	intmax_t i;

	i = (short)va_arg(*ap, int);
	return (i);
}

intmax_t	ft_cast_sl(va_list *ap)
{
	return (va_arg(*ap, long));
}

intmax_t	ft_cast_sj(va_list *ap)
{
	return (va_arg(*ap, intmax_t));
}

intmax_t	ft_cast_sz(va_list *ap)
{
	return (va_arg(*ap, size_t));
}
