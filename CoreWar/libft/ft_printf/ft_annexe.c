/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:26:59 by mconti            #+#    #+#             */
/*   Updated: 2018/05/08 11:27:01 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_ltos(t_param *p)
{
	unsigned long long	nb;
	unsigned int		i;
	unsigned int		ret;

	nb = p->param >= 0 ? p->param : -p->param;
	i = ft_log(nb, 10);
	ret = i;
	p->strparam[i] = 0;
	if (!p->param && !p->pc)
	{
		p->strparam[0] = 0;
		return (0);
	}
	while (i)
	{
		p->strparam[--i] = nb % 10 + '0';
		nb /= 10;
	}
	return (ret);
}

static unsigned int	ft_count_base(char *base)
{
	int i;
	int	j;

	if (!base)
		return (0);
	i = 0;
	while (base[i])
	{
		j = i;
		while (base[++j])
			if (base[i] == base[j])
				return (0);
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	return (i);
}

int					ft_ltos_base(t_param *p, char *base)
{
	unsigned long long	nb;
	unsigned int		i;
	unsigned int		ret;
	unsigned int		b;

	b = ft_count_base(base);
	nb = p->param;
	i = ft_log(nb, b);
	ret = i;
	p->strparam[i] = 0;
	if (!p->param && !p->pc)
	{
		p->strparam[0] = 0;
		return (0);
	}
	while (i)
	{
		p->strparam[--i] = base[nb % b];
		nb /= b;
	}
	return (ret);
}

void				ft_addtoprint(t_param *p, char c, int n)
{
	while (n)
	{
		if (p->lp == BUFF_SIZE)
			ft_toprint(p);
		p->str[p->lp++] = c;
		n--;
	}
}

void				ft_strtoprint(t_param *p, char *str, int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		while (str[i])
		{
			if (p->lp == BUFF_SIZE)
				ft_toprint(p);
			p->str[p->lp++] = str[i++];
		}
	}
	else
	{
		while (i < n && str[i])
		{
			if (p->lp == BUFF_SIZE)
				ft_toprint(p);
			p->str[p->lp++] = str[i++];
		}
	}
}
