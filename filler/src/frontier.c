/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:29:01 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/18 18:02:30 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#define Y_PLAYER ((coord >> 0x10) & 0xFFFF)
#define X_PLAYER (coord & 0xFFFF)
#define Y_ENNEMY ((coord >> 0x30) & 0xFFFF)
#define X_ENNEMY ((coord >> 0x20) & 0xFFFF)
#define X_ETOILE x - f->bestpos.x
#define Y_ETOILE y - f->bestpos.y

void	show_frontier(t_filler *f)
{
	int x;
	int y;

	y = -1;
//	dprintf(f->fd, "Player = %c\n", f->player);
	while (++y < f->ymax)
	{
		x = -1;
		while (++x < f->xmax)
		{
			if (!f->frontier[y][x])
				dprintf(f->fd, "\x1b[32m%3c", f->tab[y][x]);
			else if (f->frontier[y][x] == -1)
				dprintf(f->fd, "\x1b[31m%3c", f->tab[y][x]);
			else if (f->frontier[y][x] == 1)
				dprintf(f->fd, "\x1b[34m%3c", f->tab[y][x]);
		}
		dprintf(f->fd, "\n");
	}
	dprintf(f->fd, "\n");
}

int8_t is_player(t_filler *f, int x, int y, int player_sign)
{
	int x1;
	int y1;

	if (x < 0 || x >= f->xmax || y < 0 || y >= f->ymax)
		return (0);
	if (f->tab[y][x] != '.')
		return (f->tab[y][x] == f->player ? 1 : -1);
	if (player_sign == 1)
	{
		x1 = X_ETOILE;
		y1 = Y_ETOILE;
		if (x1 < 0 || x1 >= f->piece.xmax || y1 < 0 || y1 >= f->piece.ymax)
			return (0);
		return(f->piece.tab[y1][x1] == '*');
	}
	return (0);
}

int8_t check_pos(t_filler *f, t_pos p, int player_sign)
{
	int ret;
	int n;
	int	x1;
	int	y1;

	x1 = p.x - p.distance;
	y1 = p.y;
	ret = 0;
	while (x1 != p.x && ret != 2)
		if ((n = is_player(f, x1++, y1--, player_sign)) && n != ret)
			ret = ret ? 2 : n;
	while (y1 != p.y && ret != 2)
		if ((n = is_player(f, x1++, y1++, player_sign)) && n != ret)
			ret = ret ? 2 : n;
	while (x1 != p.x && ret != 2)
		if ((n = is_player(f, x1--, y1++, player_sign)) && n != ret)
			ret = ret ? 2 : n;
	while (y1 != p.y && ret != 2)
		if ((n = is_player(f, x1--, y1--, player_sign)) && n != ret)
			ret = ret ? 2 : n;
//	dprintf(f->fd, "x: %2i || y: %2i || dist: %2i || ret: %2i\n", p.x, p.y, p.distance, ret);
	return (ret);
}

int8_t	closest_player(t_filler *f, int x, int y, int player_sign)
{
	int	ret;
	int	n;
	t_pos p;

	p.x = x;
	p.y = y;
	p.distance = 0;
	ret = 0;
	while (++p.distance && !ret)
		ret = check_pos(f, p, player_sign);
	if (ret != 2)
		ret = (n = check_pos(f, p, player_sign)) && n != ret ? 2 : ret;
	if (ret == 2)
		ret = 0;
	return (ret);
}

void	fill_frontier(t_filler *f, int x, int y, int player_sign)
{
	int8_t pre_fill;

	pre_fill = f->frontier[y][x];
	if (f->tab[y][x] != '.')
		f->frontier[y][x] = (f->tab[y][x] == f->player) ? 3 : -3;
	else if (X_ETOILE >= 0 && X_ETOILE < f->piece.xmax && Y_ETOILE >= 0 &&
		Y_ETOILE < f->piece.ymax && f->piece.tab[Y_ETOILE][X_ETOILE] == '*')
		f->frontier[y][x] = 3;
	else
		f->frontier[y][x] = closest_player(f, x, y, player_sign) ^ 2;
	if (pre_fill != f->frontier[y][x] % 2)
	{
		if (pre_fill == 1)
			f->territory--;
		else if (f->frontier[y][x] == 3)
			f->territory++;
		if (x + 1 < f->xmax && f->frontier[y][x + 1] == -player_sign)
			fill_frontier(f, x + 1, y, player_sign);

		if (x - 1 >= 0 && f->frontier[y][x - 1] == -player_sign)
			fill_frontier(f, x - 1, y, player_sign);

		if (y + 1 < f->ymax && f->frontier[y + 1][x] == -player_sign)
			fill_frontier(f, x, y + 1, player_sign);

		if (y - 1 >= 0 && f->frontier[y - 1][x] == -player_sign)
			fill_frontier(f, x, y - 1, player_sign);

		if (x + 1 < f->xmax && y + 1 < f->ymax && f->frontier[y + 1][x + 1] == -player_sign)
			fill_frontier(f, x + 1, y + 1, player_sign);

		if (x - 1 >= 0 && y + 1 < f->ymax && f->frontier[y + 1][x - 1] == -player_sign)
			fill_frontier(f, x - 1, y + 1, player_sign);

		if (x + 1 < f->xmax && y - 1 >= 0 && f->frontier[y - 1][x + 1] == -player_sign)
			fill_frontier(f, x + 1, y - 1, player_sign);

		if (x - 1  >= 0 && y - 1 >= 0 && f->frontier[y - 1][x - 1] == -player_sign)
			fill_frontier(f, x - 1, y - 1, player_sign);
	}
}

void	update_frontier(t_filler *f, int player_sign)
{
	int x;
	int y;

	y = -1;
	while (++y < f->ymax)
	{
		x = -1;
		while (++x < f->xmax)
			if (!f->frontier[y][x])
				fill_frontier(f, x, y, player_sign);
	}
	y = -1;
	while (++y < f->ymax)
	{
		x = -1;
		while (++x < f->xmax)
			f->frontier[y][x] %= 2;
	}
	show_frontier(f);
}

void	find_coord(t_filler *f, int64_t *coord)
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
				else if (*coord < 0x100000000)
					*coord |= (y << 0x30) | (x << 0x20);
			}
		}
	}
}


int8_t	belongs_to_us(int x, int y, int64_t coord)
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

void	set_frontier(t_filler *f)
{
	int64_t	coord;
	int			x;
	int			y;

	coord = 0;
	find_coord(f, &coord);
//	dprintf(f->fd, "coord : %llX || ex = %lli || ey = %lli || px = %lli || py = %lli\n", coord, X_ENNEMY, Y_ENNEMY , X_PLAYER , Y_PLAYER);

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
