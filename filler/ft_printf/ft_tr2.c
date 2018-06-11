/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tr2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 22:22:16 by mconti            #+#    #+#             */
/*   Updated: 2018/05/08 22:22:17 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_tr_s(t_param *p)
{
	int				n;
	int				i;
	const char		*null = "(null)";

	if (!p->param)
		p->param = (uintmax_t)null;
	i = ft_strlen((char*)p->param);
	if ((!p->mlg) && (n = p->lg - (p->pc < 0 || p->pc > i ? i : p->pc)) > 0)
		ft_addtoprint(p, ' ', n);
	if (p->mlg == 2 && (n = p->lg - (p->pc < 0 || p->pc > i ? i : p->pc)) > 0)
		ft_addtoprint(p, '0', n);
	ft_strtoprint(p, (char*)p->param, p->pc);
	if (p->mlg == 1 && (n = p->lg - (p->pc < 0 || p->pc > i ? i : p->pc)) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_p(t_param *p)
{
	int				i;
	int				n;

	i = ft_ltos_base(p, "0123456789abcdef");
	if ((!p->mlg || (p->pc != -1 && p->mlg == 2)) &&
		(n = p->lg - 2 - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
	ft_strtoprint(p, "0x", 2);
	if ((n = p->pc - i) > 0)
		ft_addtoprint(p, '0', n);
	else if (p->pc == -1 && p->mlg == 2 && (n = p->lg - i - 2) > 0)
		ft_addtoprint(p, '0', n);
	ft_strtoprint(p, p->strparam, -1);
	if (p->mlg == 1 && (n = p->lg - 2 - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_lx(t_param *p)
{
	int				i;
	int				n;
	int				s;

	s = p->flag == 1 && p->param ? 2 : 0;
	i = ft_ltos_base(p, "0123456789ABCDEF");
	if ((!p->mlg || (p->pc != -1 && p->mlg == 2)) &&
		(n = p->lg - s - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
	if (s)
		ft_strtoprint(p, "0X", 2);
	if ((n = p->pc - i) > 0)
		ft_addtoprint(p, '0', n);
	else if (p->pc == -1 && p->mlg == 2 && (n = p->lg - i - s) > 0)
		ft_addtoprint(p, '0', n);
	ft_strtoprint(p, p->strparam, -1);
	if (p->mlg == 1 && (n = p->lg - s - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_lc(t_param *p)
{
	int				n;
	int				i;

	i = ft_wctos(p->param, p->strparam);
	if ((!p->mlg) && (n = p->lg - i) > 0)
		ft_addtoprint(p, ' ', n);
	else if (p->mlg == 2 && (n = p->lg - i) > 0)
		ft_addtoprint(p, '0', n);
	if (!p->param)
		ft_addtoprint(p, 0, 1);
	ft_strtoprint(p, p->strparam, -1);
	if (p->mlg == 1 && (n = p->lg - i) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_ls(t_param *p)
{
	int				n;
	int				i;
	const wchar_t	*null = L"(null)";

	if (!p->param)
		p->param = (uintmax_t)null;
	i = ft_wstos((wchar_t*)p->param, p->strparam);
	while ((p->strparam[p->pc] & 192) == 128)
		p->pc--;
	if ((!p->mlg) && (n = p->lg - (p->pc < 0 || p->pc > i ? i : p->pc)) > 0)
		ft_addtoprint(p, ' ', n);
	if (p->mlg == 2 && (n = p->lg - (p->pc < 0 || p->pc > i ? i : p->pc)) > 0)
		ft_addtoprint(p, '0', n);
	ft_strtoprint(p, p->strparam, p->pc);
	if (p->mlg == 1 && (n = p->lg - (p->pc < 0 || p->pc > i ? i : p->pc)) > 0)
		ft_addtoprint(p, ' ', n);
}
