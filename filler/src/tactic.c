/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tactic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 14:19:01 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/22 11:09:41 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int16_t	check_contact(t_filler *f)
{
	int i;
	int j;
	int b;

	j = 0;
	b = 0;
	while (j < f->piece.ymax)
	{
		i = 0;
		while (i < f->piece.xmax)
		{
			if (f->piece.tab[j][i] == '*')
			{
				if (f->piece.y + j < 0 || f->piece.y + j >= f->ymax
					|| f->piece.x + i < 0 || f->piece.x + i >= f->xmax)
					return (0);
				if (f->piece.y + j + 1 >= f->piece.ymax || f->tab[f->piece.y + j + 1][f->piece.x + i] != '.')
					b++;
				if (f->piece.y + j - 1 < 0 || f->tab[f->piece.y + j - 1][f->piece.x + i] != '.')
					b++;
				if (f->piece.x + i + 1 >= f->piece.xmax || f->tab[f->piece.y + j][f->piece.x + i + 1] != '.')
					b++;
				if (f->piece.x + i - 1 < 0 || f->tab[f->piece.y + j][f->piece.x + i - 1] != '.')
					b++;
			}
			i++;
		}
		j++;
	}
	return (b);
}

int8_t	check_placement(t_filler *f)
{
	int i;
	int j;
	int b;

	j = 0;
	b = 0;
	while (j < f->piece.ymax && !(i = 0))
	{
		while (i < f->piece.xmax)
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
			i++;
		}
		j++;
	}
	return (b == 1);
}

int16_t	best_placement(t_filler *f, uint8_t strategy)
{
	int16_t score;

	score = 0;
	f->piece.y = -f->piece.ymax;
	while (f->piece.y <= f->ymax)
	{
		f->piece.x = -f->piece.xmax;
		while (f->piece.x <= f->xmax)
		{
			if (check_placement(f))
				if ((score = f->tactic[strategy](f)) > f->bestpos.score)
				{
					f->bestpos.score = score;
					f->bestpos.x = f->piece.x;
					f->bestpos.y = f->piece.y;
				}
			f->piece.x++;
		}
		f->piece.y++;
	}
	if (!f->bestpos.score && !strategy)
		return (best_placement(f, CHECK_CONTACT));
	return (f->bestpos.score);
}
