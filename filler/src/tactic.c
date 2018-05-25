/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tactic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 01:40:10 by mconti            #+#    #+#             */
/*   Updated: 2018/05/25 01:40:12 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		check_around(t_filler *f, int i, int j, int b)
{
	if (f->piece.y + j + 1 >= f->piece.ymax ||
		f->tab[f->piece.y + j + 1][f->piece.x + i] != '.')
		b++;
	if (f->piece.y + j - 1 < 0 ||
		f->tab[f->piece.y + j - 1][f->piece.x + i] != '.')
		b++;
	if (f->piece.x + i + 1 >= f->piece.xmax ||
		f->tab[f->piece.y + j][f->piece.x + i + 1] != '.')
		b++;
	if (f->piece.x + i - 1 < 0 ||
		f->tab[f->piece.y + j][f->piece.x + i - 1] != '.')
		b++;
	return (b);
}

int16_t	check_contact(t_filler *f)
{
	int i;
	int j;
	int b;

	j = RESET;
	b = 0;
	while (++j < f->piece.ymax)
	{
		i = RESET;
		while (++i < f->piece.xmax)
			if (f->piece.tab[j][i] == '*')
			{
				if (f->piece.y + j < 0 || f->piece.y + j >= f->ymax
					|| f->piece.x + i < 0 || f->piece.x + i >= f->xmax)
					return (0);
				b = check_around(f, i, j, b);
			}
	}
	return (b);
}

int8_t	check_placement(t_filler *f)
{
	int i;
	int j;
	int b;

	j = RESET;
	b = 0;
	while (++j < f->piece.ymax && (i = RESET))
	{
		while (++i < f->piece.xmax)
		{
			if (f->piece.tab[j][i] == '*')
			{
				if (f->piece.y + j < 0 || f->piece.y + j >= f->ymax
						|| f->piece.x + i < 0 || f->piece.x + i >= f->xmax)
					return (0);
				if (f->tab[f->piece.y + j][f->piece.x + i] == f->player)
					b++;
				else if (f->tab[f->piece.y + j][f->piece.x + i] != '.')
					return (0);
			}
			if (b > 1)
				return (0);
		}
	}
	return (b == 1);
}

int16_t	best_placement(t_filler *f, uint8_t strategy)
{
	int16_t n;

	n = 0;
	f->piece.y = -f->piece.ymax;
	while (f->piece.y <= f->ymax)
	{
		f->piece.x = -f->piece.xmax;
		while (f->piece.x <= f->xmax)
		{
			if (check_placement(f))
				if ((n = f->tactic[strategy](f)) > f->bestpos.n)
				{
					f->bestpos.n = n;
					f->bestpos.x = f->piece.x;
					f->bestpos.y = f->piece.y;
				}
			f->piece.x++;
		}
		f->piece.y++;
	}
	if (!f->bestpos.n && !strategy)
		return (best_placement(f, 1));
	return (f->bestpos.n);
}
