/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:29:01 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/17 19:24:49 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#define Y_PLAYER (int16_t)((coord >> 0x10) & 0xFFFF)
#define X_PLAYER (int16_t)(coord & 0xFFFF)
#define Y_ENNEMY (int16_t)((coord >> 0x30) & 0xFFFF)
#define X_ENNEMY (int16_t)((coord >> 0x20) & 0xFFFF)

void	fill_frontier(t_filler *f, int x, int y, int player_sign)
{
	int8_t pre_fill;

	pre_fill = f->frontier[y][x];
	if (f->tab[y][x] != '.')
	{
		f->frontier[y][x] = (f->tab[y][x] == f->player) ? 1 : -1;
	//	f->territory += f->frontier[y][x] * (pre_fill != f->frontier[y][x]);
	}
	else if ()
	{

	}

	if (pre_fill != f->frontier[y][x])
	{
		if (x + 1 < xmax && f->frontier[y][x + 1] != player_sign)
			;
		if (x - 1 > 0 && f->frontier[y][x - 1] != player_sign)
			;
		if (y + 1 < ymax && f->frontier[y + 1][x] != player_sign)
			;
		if (y - 1 > 0 && f->frontier[y - 1][x] != player_sign)
			;
		
	}

}

void	update_frontier(t_filler *f, int player_sign)
{
	int x;
	int y;

	y  = -1;
	while (y++ < ymax)
	{
		x = -1;
		while (x++ < xmax)
			if (!f->frontier[y][x])
				fill_frontier(f, x, y, player_sign);
	}
	y = -1;
	while (y++ < ymax)
	{
		x = -1;
		while (x++ < xmax)
			f->frontier[y][x] %= 2;
	}
}


void	find_coord(t_filler *f, uint64_t *coord)
{
	int64_t x;
	int64_t y;

	y = -1; 
	while (++y < f->ymax)
	{
		x = -1;
		while (++x < f->xmax)
		{
			if (f->tab[y][x] != '.')
			{
				if (f->tab[y][x] == f->player)
					*coord |= (y << 0x10) | x;
				else if (*coord < 0x100)
					*coord |= (y << 0x30) | (x << 0x20);
			}
		}
	}
}


int8_t	belongs_to_us(int x, int y, uint64_t coord)
{
	int dist_y_p;
	int dist_y_e;
	int dist_x_p;
	int dist_x_e;
	
	dist_y_p = (Y_PLAYER - y) < 0 ? -(Y_PLAYER - y) : Y_PLAYER - y;
	dist_y_e = (Y_ENNEMY - y) < 0 ? -(Y_ENNEMY - y) : Y_ENNEMY - y;
	dist_x_p = (X_PLAYER - x) < 0 ? -(X_PLAYER - x) : X_PLAYER - x;
	dist_x_e = (X_ENNEMY - x) < 0 ? -(X_ENNEMY - x) : X_ENNEMY - x;
	if (dist_y_p + dist_x_p > dist_y_e + dist_x_e + 1)
		return (-1);
	return (dist_y_p + dist_x_p < dist_y_e + dist_x_e - 1);
}

void	show_frontier(t_filler *f)
{
	int x;
	int y;
	y = -1;
	while (++y < f->ymax)
	{
		x = -1;
		while (++x < f->xmax)
		{
			dprintf(f->fd, "%3d", f->frontier[y][x]);	
		}
		dprintf(f->fd, "\n");
	}
}

void	set_frontier(t_filler *f)
{
	uint64_t	coord;
	int			x;
	int			y;

	find_coord(f, &coord);
//	dprintf(f->fd, "ex = %i || ey = %i || px = %i || py = %i", X_ENNEMY, Y_ENNEMY , X_PLAYER , Y_PLAYER);
	f->frontier = (int8_t**)malloc(sizeof(int8_t*) * f->ymax);
	y = -1;
	while (++y < f->ymax)
	{
		f->frontier[y] = (int8_t*)malloc(f->xmax);
		x = -1;
		while (++x < f->xmax)
		{
			f->frontier[y][x] = belongs_to_us(x, y, coord);
			f->territory += (f->frontier[y][x] == 1);
		}
	}
	show_frontier(f);
}
