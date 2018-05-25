/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:29:01 by mconti            #+#    #+#             */
/*   Updated: 2018/05/18 18:02:30 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#define X_ETOILE x - f->bestpos.x
#define Y_ETOILE y - f->bestpos.y

int8_t	is_player(t_filler *f, int x, int y, int player_sign)
{
	int		x1;
	int		y1;

	if (x < 0 || x >= f->xmax || y < 0 || y >= f->ymax)
		return (0);
	if (f->tab[y][x] != '.')
	{
		return (f->tab[y][x] == f->player ?
			PLAYER_TERRITORY : ENNEMY_TERRITORY);
	}
	if (player_sign == PLAYER_TERRITORY)
	{
		x1 = X_ETOILE;
		y1 = Y_ETOILE;
		if (x1 < 0 || x1 >= f->piece.xmax || y1 < 0 || y1 >= f->piece.ymax)
			return (0);
		return (f->piece.tab[y1][x1] == '*');
	}
	return (0);
}

int8_t	check_pos(t_filler *f, t_pos p, int player_sign)
{
	int		ret;
	int		n;
	int		x1;
	int		y1;

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
	if (RIGHT < f->xmax && DOWN < f->ymax &&
		f->frontier[DOWN][RIGHT] == -player_sign)
		fill_frontier(f, RIGHT, DOWN, player_sign);
	if (LEFT >= 0 && DOWN < f->ymax &&
		f->frontier[DOWN][LEFT] == -player_sign)
		fill_frontier(f, LEFT, DOWN, player_sign);
	if (RIGHT < f->xmax && UP >= 0 && f->frontier[UP][RIGHT] == -player_sign)
		fill_frontier(f, RIGHT, UP, player_sign);
	if (LEFT >= 0 && UP >= 0 && f->frontier[UP][LEFT] == -player_sign)
		fill_frontier(f, LEFT, UP, player_sign);
}

void	fill_frontier(t_filler *f, int x, int y, int player_sign)
{
	int8_t	pre_fill;

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
