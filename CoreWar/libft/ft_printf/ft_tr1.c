/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tr1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:22:04 by mconti            #+#    #+#             */
/*   Updated: 2018/05/08 11:22:05 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_tr_i(t_param *p)
{
	int				i;
	int				n;
	int				s;
	const char		tab[2] = "+ ";

	s = p->param < 0 || p->flag ? 1 : 0;
	i = ft_ltos(p);
	if ((!p->mlg || (p->pc != -1 && p->mlg == 2)) &&
		(n = p->lg - s - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
	if (s)
	{
		if (p->param < 0)
			ft_addtoprint(p, '-', s);
		else if (p->flag)
			ft_addtoprint(p, tab[(int)p->flag - 1], s);
	}
	if ((n = p->pc - i) > 0)
		ft_addtoprint(p, '0', n);
	else if (p->pc == -1 && p->mlg == 2 && (n = p->lg - i - s) > 0)
		ft_addtoprint(p, '0', n);
	ft_strtoprint(p, p->strparam, -1);
	if (p->mlg == 1 && (n = p->lg - s - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_u(t_param *p)
{
	int				i;
	int				n;

	i = ft_ltos_base(p, "0123456789");
	if ((!p->mlg || (p->pc != -1 && p->mlg == 2)) &&
		(n = p->lg - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
	if ((n = p->pc - i) > 0)
		ft_addtoprint(p, '0', n);
	else if (p->pc == -1 && p->mlg == 2 && (n = p->lg - i) > 0)
		ft_addtoprint(p, '0', n);
	ft_strtoprint(p, p->strparam, -1);
	if (p->mlg == 1 && (n = p->lg - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_o(t_param *p)
{
	int				i;
	int				n;
	int				s;

	s = p->flag == 1 && (p->param || !p->pc) ? 1 : 0;
	i = ft_ltos_base(p, "01234567");
	if ((!p->mlg || (p->pc != -1 && p->mlg == 2)) &&
		(n = p->lg - s - (p->pc > i ? p->pc - s : i)) > 0)
		ft_addtoprint(p, ' ', n);
	if (s)
		ft_addtoprint(p, '0', 1);
	if ((n = p->pc - i - s) > 0)
		ft_addtoprint(p, '0', n);
	else if (p->pc == -1 && p->mlg == 2 && (n = p->lg - i - s) > 0)
		ft_addtoprint(p, '0', n);
	ft_strtoprint(p, p->strparam, -1);
	if (p->mlg == 1 && (n = p->lg - s - (p->pc > i ? p->pc - s : i)) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_x(t_param *p)
{
	int				i;
	int				n;
	int				s;

	s = p->flag == 1 && p->param ? 2 : 0;
	i = ft_ltos_base(p, "0123456789abcdef");
	if ((!p->mlg || (p->pc != -1 && p->mlg == 2)) &&
		(n = p->lg - s - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
	if (s)
		ft_strtoprint(p, "0x", 2);
	if ((n = p->pc - i) > 0)
		ft_addtoprint(p, '0', n);
	else if (p->pc == -1 && p->mlg == 2 && (n = p->lg - i - s) > 0)
		ft_addtoprint(p, '0', n);
	ft_strtoprint(p, p->strparam, -1);
	if (p->mlg == 1 && (n = p->lg - s - (p->pc > i ? p->pc : i)) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_c(t_param *p)
{
	int				n;

	if ((!p->mlg) && (n = p->lg - 1) > 0)
		ft_addtoprint(p, ' ', n);
	else if (p->mlg == 2 && (n = p->lg - 1) > 0)
		ft_addtoprint(p, '0', n);
	ft_addtoprint(p, p->param, 1);
	if (p->mlg == 1 && (n = p->lg - 1) > 0)
		ft_addtoprint(p, ' ', n);
}
