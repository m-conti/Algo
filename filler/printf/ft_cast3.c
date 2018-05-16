/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 01:13:26 by mconti            #+#    #+#             */
/*   Updated: 2018/05/09 01:13:27 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_cast_uj(va_list *ap)
{
	return (va_arg(*ap, uintmax_t));
}

intmax_t	ft_cast_uz(va_list *ap)
{
	return (va_arg(*ap, ssize_t));
}

intmax_t	ft_cast_uhh(va_list *ap)
{
	intmax_t i;

	i = (unsigned char)va_arg(*ap, unsigned int);
	return (i);
}

intmax_t	ft_cast_ull(va_list *ap)
{
	return (va_arg(*ap, unsigned long long));
}

intmax_t	ft_cast_wild(va_list *ap)
{
	return (va_arg(*ap, int));
}
