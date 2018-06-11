/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 09:49:22 by mconti            #+#    #+#             */
/*   Updated: 2018/05/07 09:49:27 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_struct.h"

int		ft_printf(char *str, ...)
{
	t_param	p;
	int		i;

	if (!str)
		return (-1);
	ft_start(&p);
	i = 0;
	va_start(p.ap, str);
	while (*str)
	{
		ft_strtoprint(&p, str, (i = ft_index(str, '%')));
		if (i >= 0)
		{
			str = ft_chflag(&str[i + 1], &p, ft_indendpar(&str[i + 1], &p));
			if (p.tr && p.tr != 16)
				p.param = g_ft[(int)p.cast].cast(&p.ap);
			g_ft[(int)p.tr].tr(&p);
		}
		else if ((i = ft_strlen(str)))
			str += i;
	}
	va_end(p.ap);
	ft_toprint(&p);
	return (p.lr);
}

void	ft_toprint(t_param *p)
{
	write(1, p->str, p->lp);
	p->lr += p->lp;
	p->lp = 0;
}

void	ft_start(t_param *p)
{
	p->lr = 0;
	p->lp = 0;
}

int		ft_setzero(t_param *p)
{
	p->param = 0;
	p->pc = -1;
	p->lg = 0;
	p->flag = 0;
	p->mlg = 0;
	return (0);
}
