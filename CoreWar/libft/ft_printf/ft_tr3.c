/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tr3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 19:12:10 by mconti            #+#    #+#             */
/*   Updated: 2018/05/14 15:44:16 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_tr_null(t_param *p)
{
	int	n;

	if (p->pc == -2)
		return ;
	if (!p->mlg && (n = p->lg - 1) > 0)
		ft_addtoprint(p, ' ', n);
	else if (p->mlg == 2 && (n = p->lg - 1) > 0)
		ft_addtoprint(p, '0', n);
	if (p->param)
		ft_addtoprint(p, p->param, 1);
	if (p->mlg == 1 && (n = p->lg - 1) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_percent(t_param *p)
{
	int	n;

	if ((!p->mlg) && (n = p->lg - 1) > 0)
		ft_addtoprint(p, ' ', n);
	else if (p->mlg == 2 && (n = p->lg - 1) > 0)
		ft_addtoprint(p, '0', n);
	ft_addtoprint(p, '%', 1);
	if (p->mlg == 1 && (n = p->lg - 1) > 0)
		ft_addtoprint(p, ' ', n);
}

void	ft_tr_ln(t_param *p)
{
	int	*len;

	len = (int*)p->param;
	if (len != NULL)
		*len = p->lp + p->lr;
}
