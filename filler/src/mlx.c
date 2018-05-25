/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 10:49:38 by mconti            #+#    #+#             */
/*   Updated: 2018/05/20 10:49:40 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "images.h"

void	init_block(t_filler *f)
{
	f->img_len[0] = 10;
	f->img_len[1] = 10;
	f->img_clr[0] = mlx_xpm_to_image(f->mlx, g_block_player, BLCX, BLCY);
	f->img_clr[1] = mlx_xpm_to_image(f->mlx, g_block_ennemy, BLCX, BLCY);
	f->img_clr[2] = mlx_xpm_to_image(f->mlx, g_block_near_ennemy, BLCX, BLCY);
	f->img_clr[3] = mlx_xpm_to_image(f->mlx, g_block_frontier, BLCX, BLCY);
	f->img_clr[4] = mlx_xpm_to_image(f->mlx, g_block_near_player, BLCX, BLCY);
}

void	init_window(t_filler *f)
{
	int			x;
	int			y;

	f->mlx = mlx_init();
	f->window = mlx_new_window(f->mlx, WINLENX, WINLENY, "Filler");
	init_block(f);
	y = RESET;
	while (++y < WINLENY)
	{
		x = RESET;
		while (++x < WINLENX)
		{
			if (INHUD)
				mlx_pixel_put(f->mlx, f->window, x, y, COLOR_HUD);
			else if (INMAP)
				mlx_pixel_put(f->mlx, f->window, x, y, COLOR_MAP);
			else
				mlx_pixel_put(f->mlx, f->window, x, y, COLOR_BACK);
		}
	}
	mlx_string_put(f->mlx, f->window, NAMEPX, NAMESY, COLOR_PLAYER, PNAME);
	mlx_string_put(f->mlx, f->window, NAMEPX, NAMESY + 2, COLOR_FRONT, PNAME);
	mlx_string_put(f->mlx, f->window, VSX, NAMESY, COLOR_FRONT, "VS");
	mlx_string_put(f->mlx, f->window, NAMEEX, NAMESY, COLOR_ENNEMY, ENAME);
	mlx_string_put(f->mlx, f->window, NAMEEX, NAMESY + 2, COLOR_FRONT, ENAME);
}

void	print_block(t_filler *f, int x, int y, int8_t type)
{
	x = MARGECASE + MAPXMIN + (x * CASELEN);
	y = MARGECASE + MAPYMIN + (y * CASELEN);
	mlx_put_image_to_window(f->mlx, f->window, f->img_clr[type], x, y);
}

void	print_point(t_filler *f, int x, int y, int8_t type)
{
	int			i;
	int			j;
	const int	color[5] = {COLOR_PLAYER,
						COLOR_ENNEMY,
						COLOR_NEXT_ENNEMY,
						COLOR_FRONT,
						COLOR_NEXT_PLAYER};

	if (type > 4 || type < 0)
		return ;
	x = MARGECASE + MAPXMIN + (x * CASELEN);
	y = MARGECASE + MAPYMIN + (y * CASELEN);
	j = RESET;
	while (++j < POINTLEN)
	{
		i = RESET;
		while (++i < POINTLEN)
			mlx_pixel_put(f->mlx, f->window, x + i, y + j, color[type]);
	}
}

void	print_hud(t_filler *f)
{
	int			i;
	int			j;

	j = HUDYMIN;
	while (++j < HUDYMAX - 1)
	{
		i = HUDXMIN;
		while (++i < HUDXMAX - 1)
		{
			if (i == (HUDLENX / 2) + HUDXMIN)
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_FRONT);
			else if (i < HUDXMIN + (f->player_territory * HUDLENX) / NBCASES)
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_PLAYER);
			else if (i < HUDXMIN + (f->territory * HUDLENX) / NBCASES)
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_NEXT_PLAYER);
			else if (i > HUDXMAX - (f->ennemy_territory * HUDLENX) / NBCASES)
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_ENNEMY);
			else
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_NEXT_ENNEMY);
		}
	}
	mlx_do_sync(f->mlx);
}
