/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 04:59:53 by mconti            #+#    #+#             */
/*   Updated: 2018/05/25 04:59:55 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	find_coord(t_filler *f, int64_t *coord)
{
	int64_t	x;
	int64_t	y;

	y = RESET;
	while (++y < f->ymax)
	{
		x = RESET;
		while (++x < f->xmax)
			if (f->tab[y][x] != '.')
			{
				if (f->tab[y][x] == f->player)
				{
					if (VISUAL == ON)
						print_block(f, x, y, 0);
					*coord |= (y << TWO_BYTES) | x;
				}
				else if (*coord <= INT_MAX)
				{
					if (VISUAL == ON)
						print_block(f, x, y, 1);
					*coord |= (y << SIX_BYTES) | (x << FOUR_BYTES);
				}
			}
	}
}

int8_t	belongs_to_us(int x, int y, int64_t coord)
{
	int		dist_y_p;
	int		dist_y_e;
	int		dist_x_p;
	int		dist_x_e;

	dist_y_p = (Y_PLAYER - y) < 0 ? -(Y_PLAYER - y) : Y_PLAYER - y;
	dist_y_e = (Y_ENNEMY - y) < 0 ? -(Y_ENNEMY - y) : Y_ENNEMY - y;
	dist_x_p = (X_PLAYER - x) < 0 ? -(X_PLAYER - x) : X_PLAYER - x;
	dist_x_e = (X_ENNEMY - x) < 0 ? -(X_ENNEMY - x) : X_ENNEMY - x;
	if (dist_y_p + dist_x_p > dist_y_e + dist_x_e + 1)
		return (ENNEMY_TERRITORY);
	return (dist_y_p + dist_x_p < dist_y_e + dist_x_e - 1);
}

void	set_frontier(t_filler *f)
{
	int64_t	coord;
	int		x;
	int		y;

	if (VISUAL == ON)
		init_window(f);
	coord = 0;
	find_coord(f, &coord);
	f->frontier = (int8_t**)malloc(sizeof(int8_t*) * f->ymax);
	y = RESET;
	while (++y < f->ymax)
	{
		f->frontier[y] = (int8_t*)malloc(f->xmax);
		x = RESET;
		while (++x < f->xmax)
		{
			f->frontier[y][x] = belongs_to_us(x, y, coord);
			f->territory += (f->frontier[y][x] == PLAYER_TERRITORY);
		}
	}
}
