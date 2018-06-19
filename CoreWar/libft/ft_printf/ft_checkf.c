/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 17:54:02 by mconti            #+#    #+#             */
/*   Updated: 2018/04/22 17:54:04 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_indendpar(char *str, t_param *p)
{
	int				i;

	i = -1;
	while (str[++i])
		if ((p->tr = ft_memindex("\0iduoxcspnDUOXCS%", str[i], 17)) >= 0)
		{
			p->cast = -ft_isupper(str[i]);
			return (i);
		}
	p->tr = 0;
	return (i);
}

char			*ft_chflag(char *str, t_param *p, unsigned int end)
{
	unsigned int	i;
	int				stop;

	i = 0;
	stop = ft_setzero(p);
	while (i < end && stop != -1)
	{
		stop = ft_setflag(p, ft_memindex("-0#+ hljz", str[i], 9), str[i]);
		if (stop == 1)
			i = ft_setlargeur(str, p, i);
		if (stop != -1)
			i++;
	}
	if (i != end && !(p->tr = 0))
		p->param = str[i];
	ft_setcast(p);
	i += !str[i] ? 0 : 1;
	return (&str[i]);
}

unsigned int	ft_setlargeur(char *str, t_param *p, unsigned int i)
{
	if (str[i] == '.' && p->pc == -1)
	{
		if (str[i + 1] != '*')
			p->pc = ft_atoi(&str[i + 1]);
		else if (++i)
		{
			p->pc = ft_cast_wild(&p->ap);
			p->pc = p->pc < 0 ? -1 : p->pc;
		}
	}
	else if (str[i] != '.')
	{
		if (str[i] != '*')
			p->lg = ft_atoi(&str[i]);
		else
		{
			if ((p->lg = ft_cast_wild(&p->ap)) < 0)
				p->mlg = 1;
			p->lg = ft_abs(p->lg);
		}
	}
	while (ft_isdigit(str[i + 1]) && str[i] != '*')
		i++;
	return (i);
}

int				ft_setflag(t_param *p, int flag, char c)
{
	if (flag < 0)
		return (ft_isdigit(c) || c == '.' || c == '*' ? 1 : -1);
	if (flag < 2)
	{
		if (!p->mlg || p->mlg == 2)
			p->mlg = flag + 1;
	}
	else if (flag < 5)
	{
		if ((flag == 2 && (p->tr < 4 || p->tr == 10)) ||
			(flag == 3 && p->tr > 2 && p->tr != 9))
			return (0);
		if (!p->flag || p->flag == 2)
			p->flag = flag == 2 ? flag - 1 : flag - 2;
	}
	else if (p->cast != -1 || (p->tr == 13 && !(p->cast = 0)))
	{
		if (p->cast && p->cast < 3 && p->cast == flag - 4)
			p->cast += 4;
		else if (p->cast < flag - 4 || p->cast == 5)
			p->cast = flag - 4;
	}
	return (0);
}

void			ft_setcast(t_param *p)
{
	const char		cast[9] = {0, 0, 7, 7, 7, 14, 15, 11, 11};
	char			z;

	if (p->cast == -1)
	{
		if (p->tr == 13)
			p->cast = 7;
		else if (p->tr < 13)
			p->cast = 2;
		else if (p->tr == 14)
			p->cast = 16;
		else
			p->cast = 17;
	}
	else if (p->tr && p->tr < 16)
	{
		z = p->tr == 13 ? 7 : cast[p->tr - 1];
		if (p->tr > 5 && (p->cast != 2 || p->tr == 8 || p->tr == 9)
		&& p->tr != 13)
			p->cast = z;
		else
			p->cast += z;
		if ((p->tr & 14) == 6 && p->cast >= 16)
			p->tr += 8;
	}
}
