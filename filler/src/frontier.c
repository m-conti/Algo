/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:29:01 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/18 17:47:04 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#define Y_PLAYER (int16_t)((coord >> 0x10) & 0xFFFF)
#define X_PLAYER (int16_t)(coord & 0xFFFF)
#define Y_ENNEMY (int16_t)((coord >> 0x30) & 0xFFFF)
#define X_ENNEMY (int16_t)((coord >> 0x20) & 0xFFFF)


int		closest_player(f_filler *f, int x, int y)
{
	
}

void	fill_frontier(t_filler *f, int x, int y, int player_sign, int nfront)
{
	int8_t pre_fill;

	pre_fill = f->frontier[nfront][y][x];
	if (f->tab[y][x] != '.')
	{
		f->frontier[nfront][y][x] = (f->tab[y][x] == f->player) ? 3 : -3;
	//	f->territory += f->frontier[nfront][y][x] * (pre_fill != f->frontier[y][x]);
	}
	else
	{
		f->frontier[nfront][y][x] = closest_player(f, x, y) ^ 2;
	}
	
	if (pre_fill != f->frontier[nfront][y][x])
	{
		if (x + 1 < xmax && f->frontier[nfront][y][x + 1] == -player_sign)
			fill_frontier(f, x + 1, y, player_sign, nfront);
		if (x - 1 > 0 && f->frontier[nfront][y][x - 1] == -player_sign)
			fill_frontier(f, x - 1, y, player_sign, nfront);
		if (y + 1 < ymax && f->frontier[y + 1][x] == -player_sign);
			fill_frontier(f, x, y + 1, player_sign, nfront);
		if (y - 1 > 0 && f->frontier[y - 1][x] == -player_sign)
			fill_frontier(f, x, y - 1, player_sign, nfront);
		
	}

}

void	update_frontier(t_filler *f, int player_sign, int nfront)
{
	int x;
	int y;

	y  = -1;
	while (y++ < ymax)
	{
		x = -1;
		while (x++ < xmax)
			if (!f->frontier[nfront][y][x])
				fill_frontier(f, x, y, player_sign);
	}
	y = -1;
	while (y++ < ymax)
	{
		x = -1;
		while (x++ < xmax)
			f->frontier[nfront][y][x] %= 2;
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
			dprintf(f->fd, "%3d", f->frontier[0][y][x]);	
		}
		dprintf(f->fd, "\n");
	}
}

void	set_frontier(t_filler *f)
{
	uint64_t	coord;
	int			x;
	int			y;
	int			i;

	find_coord(f, &coord);
//	dprintf(f->fd, "ex = %i || ey = %i || px = %i || py = %i", X_ENNEMY, Y_ENNEMY , X_PLAYER , Y_PLAYER);
	
	i = -1;
	while (++i < 2)
	{
		f->frontier[i] = (int8_t**)malloc(sizeof(int8_t*) * f->ymax);
		y = -1;
		while (++y < f->ymax)
		{
			f->frontier[i][y] = (int8_t*)malloc(f->xmax);
			x = -1;
			while (++x < f->xmax)
			{
				f->frontier[i][y][x] = belongs_to_us(x, y, coord);
				f->territory += (f->frontier[i][y][x] == 1);
			}
		}
	}
	show_frontier(f); //
}
