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

int8_t is_player(f_filler *f, int x, int y)
{
	if (x < 0 || x >= f->xmax || y < 0 || y >= f->ymax)
		return (0);
	if (f->tab[y][x] != '.')
		return (f->tab[y][x] == f->player ? 1 : -1);
	x -= f->piece.x;
	y -= f->piece.y;
	if (x < 0 || x >= f->piece.xmax || y < 0 || y >= f->piece.ymax)
		return (0);
	return(f->piece.tab[y][x] == '*');
}

int8_t check_pos(f_filler *f, int x, int y, int distance)
{
	int ret;

	x1 = x - distance;
	y1 = y;
	while (x1 != x)
		ret = is_player(f, x1++, y1--);
	while (y1 != y)
		ret = is_player(f, x1++, y1++);
	while (x1 != x)
		ret = is_player(f, x1--, y1++);
	while (y1 != y)
		ret = is_player(f, x1--, y1--);
}

int8_t	closest_player(f_filler *f, int x, int y)
{
	int	distance;
	int	stop;
	int	ret;

	distance = 0;
	ret = 0;
	while (++distance && !ret)
		ret = check_pos(f, x, y, distance);
}

void	fill_frontier(t_filler *f, int x, int y, int player_sign)
{
	int8_t pre_fill;

	pre_fill = f->frontier[y][x];
	if (f->tab[y][x] != '.')
		f->frontier[y][x] = (f->tab[y][x] == f->player) ? 3 : -3;
	else
		f->frontier[y][x] = closest_player(f, x, y) ^ 2;
	if (pre_fill != f->frontier[y][x] % 2)
	{
		if (pre_fill == 1)
			f->territory--;
		else if (f->frontier[y][x] == 3)
			f->territory++;
		if (x + 1 < xmax && f->frontier[y][x + 1] == -player_sign)
			fill_frontier(f, x + 1, y, player_sign);
		if (x - 1 > 0 && f->frontier[y][x - 1] == -player_sign)
			fill_frontier(f, x - 1, y, player_sign);
		if (y + 1 < ymax && f->frontier[y + 1][x] == -player_sign);
			fill_frontier(f, x, y + 1, player_sign);
		if (y - 1 > 0 && f->frontier[y - 1][x] == -player_sign)
			fill_frontier(f, x, y - 1, player_sign);	
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
	show_frontier(f);
}
