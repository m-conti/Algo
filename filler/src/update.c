/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 05:02:39 by mconti            #+#    #+#             */
/*   Updated: 2018/05/25 05:02:41 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	draw_frontier(t_filler *f, int x, int y)
{
	if ((LEFT >= 0 && (f->frontier[y][LEFT]) == PLAYER_TERRITORY)
	|| (RIGHT < f->xmax && (f->frontier[y][RIGHT]) == PLAYER_TERRITORY)
	|| (UP >= 0 && (f->frontier[UP][x]) == PLAYER_TERRITORY)
	|| (DOWN < f->ymax && (f->frontier[DOWN][x]) == PLAYER_TERRITORY))
		return ;
	f->frontier[y][x] = ENNEMY_TERRITORY;
}

void	draw_print_frontier(t_filler *f)
{
	int		x;
	int		y;

	y = RESET;
	while (++y < f->ymax)
	{
		x = RESET;
		while (++x < f->xmax)
		{
			if (!f->frontier[y][x])
				draw_frontier(f, x, y);
			if (VISUAL == ON && f->tab[y][x] == '.')
				print_block(f, x, y, f->frontier[y][x] + 3);
			else
			{
				f->tab[y][x] == f->player ?
				f->player_territory++ : f->ennemy_territory++;
				if (VISUAL == ON)
					print_block(f, x, y, (f->frontier[y][x] & 2) >> 1);
			}
		}
	}
}

void	update_frontier(t_filler *f, int player_sign)
{
	int		x;
	int		y;

	y = RESET;
	while (++y < f->ymax)
	{
		x = RESET;
		while (++x < f->xmax)
			if (!f->frontier[y][x])
				fill_frontier(f, x, y, player_sign);
	}
	y = RESET;
	while (++y < f->ymax)
	{
		x = RESET;
		while (++x < f->xmax)
		{
			f->frontier[y][x] %= 2;
		}
	}
	draw_print_frontier(f);
}

int16_t	update_frontier_test(t_filler *f)
{
	int		x;
	int		y;
	int16_t	ret;

	y = RESET;
	ret = 0;
	while (++y < f->ymax)
	{
		x = RESET;
		while (++x < f->xmax)
			if (!f->frontier[y][x])
				ret += fill_frontier_test(f, x, y);
	}
	y = RESET;
	while (++y < f->ymax)
	{
		x = RESET;
		while (++x < f->xmax)
			f->frontier[y][x] %= 2;
	}
	return (ret);
}
