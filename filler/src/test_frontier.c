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

int8_t is_player_test(t_filler *f, int x, int y)
{
	int x1;
	int y1;

	if (x < 0 || x >= f->xmax || y < 0 || y >= f->ymax)
		return (0);
	if (f->tab[y][x] != '.')
		return (f->tab[y][x] == f->player ? 1 : -1);
	x1 = X_ETOILE;
	y1 = Y_ETOILE;
	if (x1 < 0 || x1 >= f->piece.xmax || y1 < 0 || y1 >= f->piece.ymax)
		return (0);
	return(f->piece.tab[y1][x1] == '*');
}

int8_t check_pos_test(t_filler *f, t_pos p)
{
	int ret;
	int n;
	int	x1;
	int	y1;

	x1 = p.x - p.distance;
	y1 = p.y;
	ret = 0;
	while (x1 != p.x && ret != 2)
		if ((n = is_player_test(f, x1++, y1--)) && n != ret)
			ret = ret ? 2 : n;
	while (y1 != p.y && ret != 2)
		if ((n = is_player_test(f, x1++, y1++)) && n != ret)
			ret = ret ? 2 : n;
	while (x1 != p.x && ret != 2)
		if ((n = is_player_test(f, x1--, y1++)) && n != ret)
			ret = ret ? 2 : n;
	while (y1 != p.y && ret != 2)
		if ((n = is_player_test(f, x1--, y1--)) && n != ret)
			ret = ret ? 2 : n;
//	dprintf(f->fd, "x: %2i || y: %2i || dist: %2i || ret: %2i\n", p.x, p.y, p.distance, ret);
	return (ret);
}

int8_t	closest_player_test(t_filler *f, int x, int y)
{
	int	ret;
	int	n;
	t_pos p;

	p.x = x;
	p.y = y;
	p.distance = 0;
	ret = 0;
	while (++p.distance && !ret)
		ret = check_pos_test(f, p);
	if (ret != 2)
		ret = (n = check_pos_test(f, p)) && n != ret ? 2 : ret;
	if (ret == 2)
		ret = 0;
	return (ret);
}

int16_t	fill_frontier_test(t_filler *f, int x, int y)
{
	int8_t pre_fill;
	int16_t ret;

	ret = 0;
	pre_fill = f->frontier[y][x];
//	dprintf(f->fd, "pre_fill: %-2hhi", pre_fill);
	if (f->tab[y][x] != '.')
		f->frontier[y][x] = -3;
	else if (X_ETOILE >= 0 && X_ETOILE < f->piece.xmax && Y_ETOILE >= 0 &&
		Y_ETOILE < f->piece.ymax && f->piece.tab[Y_ETOILE][X_ETOILE] == '*')
		f->frontier[y][x] = 3;
	else
		f->frontier[y][x] = closest_player_test(f, x, y) ^ 2;
	if (pre_fill != f->frontier[y][x] % 2)
	{
		if (f->frontier[y][x] == 3)
			ret++;
		if (x + 1 < f->xmax && f->frontier[y][x + 1] == -1)
			ret += fill_frontier_test(f, x + 1, y);
		if (x - 1 > 0 && f->frontier[y][x - 1] == -1)
			ret += fill_frontier_test(f, x - 1, y);
		if (y + 1 < f->ymax && f->frontier[y + 1][x] == -1)
			ret += fill_frontier_test(f, x, y + 1);
		if (y - 1 > 0 && f->frontier[y - 1][x] == -1)
			ret += fill_frontier_test(f, x, y - 1);
		if (x + 1 < f->xmax && y + 1 < f->ymax && f->frontier[y + 1][x + 1] == -1)
			ret += fill_frontier_test(f, x + 1, y + 1);

		if (x - 1 >= 0 && y + 1 < f->ymax && f->frontier[y + 1][x - 1] == -1)
			ret += fill_frontier_test(f, x - 1, y + 1);

		if (x + 1 < f->xmax && y - 1 >= 0 && f->frontier[y - 1][x + 1] == -1)
			ret += fill_frontier_test(f, x + 1, y - 1);

		if (x - 1  >= 0 && y - 1 >= 0 && f->frontier[y - 1][x - 1] == -1)
			ret += fill_frontier_test(f, x - 1, y - 1);
	}
	f->frontier[y][x] = pre_fill ^ 2;
	return (ret);
}

int16_t	update_frontier_test(t_filler *f)
{
	int 		x;
	int 		y;
	int16_t		ret;

	y = -1;
	ret = 0;
	while (++y < f->ymax)
	{
		x = -1;
		while (++x < f->xmax)
			if (!f->frontier[y][x])
				ret += fill_frontier_test(f, x, y);
	}
	y = -1;
	while (++y < f->ymax)
	{
		x = -1;
		while (++x < f->xmax)
			f->frontier[y][x] %= 2;
	}
	//dprintf(f->fd, "%hi\n", ret);
	return (f->territory + ret);
}
