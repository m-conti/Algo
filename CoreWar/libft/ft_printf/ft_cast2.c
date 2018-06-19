/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 01:13:20 by mconti            #+#    #+#             */
/*   Updated: 2018/05/09 01:13:22 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_cast_shh(va_list *ap)
{
	intmax_t i;

	i = (char)va_arg(*ap, int);
	return (i);
}

intmax_t	ft_cast_sll(va_list *ap)
{
	return (va_arg(*ap, long long));
}

intmax_t	ft_cast_ui(va_list *ap)
{
	return (va_arg(*ap, unsigned int));
}

intmax_t	ft_cast_uh(va_list *ap)
{
	intmax_t i;

	i = (unsigned short)va_arg(*ap, unsigned int);
	return (i);
}

intmax_t	ft_cast_ul(va_list *ap)
{
	return (va_arg(*ap, unsigned long));
}
