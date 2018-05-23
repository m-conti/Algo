/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:29:01 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/22 17:01:28 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	show_frontier(t_filler *f)
{
	int x;
	int y;

	y = RESET_COUNT;
//	dprintf(f->fd, "Player = %c\n", f->player);
	while (++y < f->ymax)
	{
		x = RESET_COUNT;
		while (++x < f->xmax)
		{
			;
//			if (!(f->frontier[y][x] % 2))
//				dprintf(f->fd, "\x1b[32m%3c", f->tab[y][x]);
//			else if (f->frontier[y][x] % 2 == ENNEMY_TERRITORY)
//				dprintf(f->fd, "\x1b[31m%3c", f->tab[y][x]);
//			else if (f->frontier[y][x] % 2 == PLAYER_TERRITORY)
//				dprintf(f->fd, "\x1b[34m%3c", f->tab[y][x]);
		}
	//	dprintf(f->fd, "\n");
	}
	//dprintf(f->fd, "\n");
}

int8_t is_player(t_filler *f, int x, int y, int player_sign)
{
	int x1;
	int y1;

	if (x < 0 || x >= f->xmax || y < 0 || y >= f->ymax)
		return (0);
	if (f->tab[y][x] != '.')
		return (f->tab[y][x] == f->player ? PLAYER_TERRITORY : ENNEMY_TERRITORY);
	if (player_sign == PLAYER_TERRITORY)
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
	while (x1 != p.x && ret != LOST_TERRITORY)
		if ((n = is_player(f, x1++, y1--, player_sign)) && n != ret)
			ret = ret ? LOST_TERRITORY : n;
	while (y1 != p.y && ret != LOST_TERRITORY)
		if ((n = is_player(f, x1++, y1++, player_sign)) && n != ret)
			ret = ret ? LOST_TERRITORY : n;
	while (x1 != p.x && ret != LOST_TERRITORY)
		if ((n = is_player(f, x1--, y1++, player_sign)) && n != ret)
			ret = ret ? LOST_TERRITORY : n;
	while (y1 != p.y && ret != LOST_TERRITORY)
		if ((n = is_player(f, x1--, y1--, player_sign)) && n != ret)
			ret = ret ? LOST_TERRITORY : n;
	return (ret);
}

int8_t	closest_player(t_filler *f, int x, int y, int player_sign)
{
	int		ret;
	int		n;
	t_pos	p;

	p.x = x;
	p.y = y;
	p.distance = 0;
	ret = 0;
	while (++p.distance && !ret)
		ret = check_pos(f, p, player_sign);
	if (ret != LOST_TERRITORY)
		if ((n = check_pos(f, p, player_sign)) && n != ret)
			ret = LOST_TERRITORY;
	if (ret == LOST_TERRITORY)
		ret = 0;
	return (ret);
}

void	move_next_frontier(t_filler *f, int x, int y, int player_sign)
{
	if (RIGHT < f->xmax && f->frontier[y][RIGHT] == -player_sign)
		fill_frontier(f, RIGHT, y, player_sign);
	if (LEFT >= 0 && f->frontier[y][LEFT] == -player_sign)
		fill_frontier(f, LEFT, y, player_sign);
	if (DOWN < f->ymax && f->frontier[DOWN][x] == -player_sign)
		fill_frontier(f, x, DOWN, player_sign);
	if (UP >= 0 && f->frontier[UP][x] == -player_sign)
		fill_frontier(f, x, UP, player_sign);
	if (RIGHT < f->xmax && DOWN < f->ymax && f->frontier[DOWN][RIGHT] == -player_sign)
		fill_frontier(f, RIGHT, DOWN, player_sign);
	if (LEFT >= 0 && DOWN < f->ymax && f->frontier[DOWN][LEFT] == -player_sign)
		fill_frontier(f, LEFT, DOWN, player_sign);
	if (RIGHT < f->xmax && UP >= 0 && f->frontier[UP][RIGHT] == -player_sign)
		fill_frontier(f, RIGHT, UP, player_sign);
	if (LEFT  >= 0 && UP >= 0 && f->frontier[UP][LEFT] == -player_sign)
		fill_frontier(f, LEFT, UP, player_sign);
}

void	fill_frontier(t_filler *f, int x, int y, int player_sign)
{
	int8_t pre_fill;

	pre_fill = f->frontier[y][x];
	if (f->tab[y][x] != '.')
		f->frontier[y][x] = (f->tab[y][x] == f->player) ?
			NEW_PLAYER_TERRITORY : NEW_ENNEMY_TERRITORY;
	else if (X_ETOILE >= 0 && X_ETOILE < f->piece.xmax && Y_ETOILE >= 0 &&
		Y_ETOILE < f->piece.ymax && f->piece.tab[Y_ETOILE][X_ETOILE] == '*')
		f->frontier[y][x] = NEW_PLAYER_TERRITORY;
	else
		f->frontier[y][x] = closest_player(f, x, y, player_sign) ^ 2;
	if (pre_fill != f->frontier[y][x] % 2)
	{
		if (pre_fill == PLAYER_TERRITORY)
			f->territory--;
		else if (f->frontier[y][x] == NEW_PLAYER_TERRITORY)
			f->territory++;
		move_next_frontier(f, x, y, player_sign);
	}
}

void	draw_frontier(t_filler *f, int x, int y)
{
	if ((LEFT >= 0 && (f->frontier[y][LEFT]) == PLAYER_TERRITORY)
	|| (RIGHT < f->xmax && (f->frontier[y][RIGHT]) == PLAYER_TERRITORY)
	|| (UP >= 0 && (f->frontier[UP][x]) == PLAYER_TERRITORY)
	|| (DOWN < f->ymax && (f->frontier[DOWN][x]) == PLAYER_TERRITORY))
		return ;
	f->frontier[y][x] = ENNEMY_TERRITORY;
}

void	update_frontier(t_filler *f, int player_sign)
{
	int x;
	int y;

	y = RESET_COUNT;
	while (++y < f->ymax)
	{
		x = RESET_COUNT;
		while (++x < f->xmax)
			if (!f->frontier[y][x])
				fill_frontier(f, x, y, player_sign);
	}
	y = RESET_COUNT;
	while (++y < f->ymax)
	{
		x = RESET_COUNT;
		while (++x < f->xmax)
		{
			f->frontier[y][x] %= 2;
		}
	}
	y = RESET_COUNT;
	while (++y < f->ymax)
	{
		x = RESET_COUNT;
		while (++x < f->xmax)
		{
			if (!f->frontier[y][x] && player_sign == ENNEMY_TERRITORY)
				draw_frontier(f, x, y);
		}
	}
	if (f->display && player_sign == 1)
		display_frontier(f);
}

void	find_coord(t_filler *f, int64_t *coord)
{
	int64_t x;
	int64_t y;

	y = RESET_COUNT;
	while (++y < f->ymax)
	{
		x = RESET_COUNT;
		while (++x < f->xmax)
		{
			if (f->tab[y][x] != '.')
			{
				if (f->tab[y][x] == f->player)
					*coord |= (y << TWO_BYTES) | x;
				else if (*coord <= INT_MAX)
					*coord |= (y << SIX_BYTES) | (x << FOUR_BYTES);
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
		return (ENNEMY_TERRITORY);
	return (dist_y_p + dist_x_p < dist_y_e + dist_x_e - 1);
}

void	set_frontier(t_filler *f)
{
	int64_t		coord;
	int			x;
	int			y;

	coord = 0;
	find_coord(f, &coord);
	f->frontier = (int8_t**)malloc(sizeof(int8_t*) * f->ymax);
	y = RESET_COUNT;
	while (++y < f->ymax)
	{
		f->frontier[y] = (int8_t*)malloc(f->xmax);
		x = RESET_COUNT;
		while (++x < f->xmax)
		{
			f->frontier[y][x] = belongs_to_us(x, y, coord);
			f->territory += (f->frontier[y][x] == PLAYER_TERRITORY);
		}
	}
}
