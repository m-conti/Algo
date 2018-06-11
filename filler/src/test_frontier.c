/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_frontier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 19:44:57 by mconti            #+#    #+#             */
/*   Updated: 2018/05/18 19:44:59 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#define X_ETOILE x - f->piece.x
#define Y_ETOILE y - f->piece.y

int8_t	is_player_test(t_filler *f, int x, int y)
{
	int		x1;
	int		y1;

	if (x < 0 || x >= f->xmax || y < 0 || y >= f->ymax)
		return (0);
	if (f->tab[y][x] != '.')
		return (f->tab[y][x] == f->player ? 1 : ENNEMY_TERRITORY);
	x1 = X_ETOILE;
	y1 = Y_ETOILE;
	if (x1 < 0 || x1 >= f->piece.xmax || y1 < 0 || y1 >= f->piece.ymax)
		return (0);
	return (f->piece.tab[y1][x1] == '*');
}

int8_t	check_pos_test(t_filler *f, t_pos p)
{
	int		ret;
	int		n;
	int		x1;
	int		y1;

	x1 = p.x - p.distance;
	y1 = p.y;
	ret = 0;
	while (x1 != p.x && ret != LOST_TERRITORY)
		if ((n = is_player_test(f, x1++, y1--)) && n != ret)
			ret = ret ? LOST_TERRITORY : n;
	while (y1 != p.y && ret != LOST_TERRITORY)
		if ((n = is_player_test(f, x1++, y1++)) && n != ret)
			ret = ret ? LOST_TERRITORY : n;
	while (x1 != p.x && ret != LOST_TERRITORY)
		if ((n = is_player_test(f, x1--, y1++)) && n != ret)
			ret = ret ? LOST_TERRITORY : n;
	while (y1 != p.y && ret != LOST_TERRITORY)
		if ((n = is_player_test(f, x1--, y1--)) && n != ret)
			ret = ret ? LOST_TERRITORY : n;
	return (ret);
}

int8_t	closest_player_test(t_filler *f, int x, int y)
{
	int		ret;
	int		n;
	t_pos	p;

	p.x = x;
	p.y = y;
	p.distance = 0;
	ret = 0;
	while (++p.distance && !ret)
		ret = check_pos_test(f, p);
	if (ret != LOST_TERRITORY)
		if ((n = check_pos_test(f, p)) && n != ret)
			ret = LOST_TERRITORY;
	if (ret == LOST_TERRITORY)
		ret = 0;
	return (ret);
}

int16_t	move_next_frontier_test(t_filler *f, int x, int y, int16_t ret)
{
	if (f->frontier[y][x] == NEW_PLAYER_TERRITORY)
		ret++;
	if (RIGHT < f->xmax && f->frontier[y][RIGHT] == ENNEMY_TERRITORY)
		ret += fill_frontier_test(f, RIGHT, y);
	if (LEFT > 0 && f->frontier[y][LEFT] == ENNEMY_TERRITORY)
		ret += fill_frontier_test(f, LEFT, y);
	if (DOWN < f->ymax && f->frontier[DOWN][x] == ENNEMY_TERRITORY)
		ret += fill_frontier_test(f, x, DOWN);
	if (UP > 0 && f->frontier[UP][x] == ENNEMY_TERRITORY)
		ret += fill_frontier_test(f, x, UP);
	if (RIGHT < f->xmax && DOWN < f->ymax &&
		f->frontier[DOWN][RIGHT] == ENNEMY_TERRITORY)
		ret += fill_frontier_test(f, RIGHT, DOWN);
	if (LEFT >= 0 && DOWN < f->ymax &&
		f->frontier[DOWN][LEFT] == ENNEMY_TERRITORY)
		ret += fill_frontier_test(f, LEFT, DOWN);
	if (RIGHT < f->xmax && UP >= 0 &&
		f->frontier[UP][RIGHT] == ENNEMY_TERRITORY)
		ret += fill_frontier_test(f, RIGHT, UP);
	if (LEFT >= 0 && UP >= 0 && f->frontier[UP][LEFT] == ENNEMY_TERRITORY)
		ret += fill_frontier_test(f, LEFT, UP);
	return (ret);
}

int16_t	fill_frontier_test(t_filler *f, int x, int y)
{
	int8_t	pre_fill;
	int16_t	ret;

	ret = 0;
	pre_fill = f->frontier[y][x];
	if (f->tab[y][x] != '.')
		f->frontier[y][x] = NEW_ENNEMY_TERRITORY;
	else if (X_ETOILE >= 0 && X_ETOILE < f->piece.xmax && Y_ETOILE >= 0 &&
		Y_ETOILE < f->piece.ymax && f->piece.tab[Y_ETOILE][X_ETOILE] == '*')
		f->frontier[y][x] = NEW_PLAYER_TERRITORY;
	else
		f->frontier[y][x] = closest_player_test(f, x, y) ^ 2;
	if (pre_fill != f->frontier[y][x] % 2)
		ret = move_next_frontier_test(f, x, y, ret);
	f->frontier[y][x] = pre_fill ^ 2;
	return (ret);
}
