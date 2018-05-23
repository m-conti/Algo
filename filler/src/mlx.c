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
#define RESET -1

/*					TAILLE ANNEXE				*/
#define MARGELEN			10
#define POINTLEN			(200 / f->ymax)
#define MARGECASE			1
#define CASELEN				(POINTLEN + MARGECASE)

/*					TAILLE MAP					*/
#define MAPLENY				(f->ymax * CASELEN + MARGECASE)
#define MAPLENX				(f->xmax * CASELEN + MARGECASE)

/*					TAILLE HUD					*/
#define HUDLENY				40
#define HUDLENX				(MAPLENX - 2 * MARGELEN)

/*				TAILLE WINDOW			*/
#define WINLENY				(MAPLENY + HUDLENY + 3 * MARGELEN)
#define WINLENX				(MAPLENX + 2 * MARGELEN)

/*					POINTS HUD					*/
#define HUDXMIN				(2 * MARGELEN)
#define HUDXMAX				(HUDXMIN + HUDLENX)
#define HUDYMIN				MARGELEN
#define HUDYMAX				(HUDYMIN + HUDLENY)

/*					POINTS MAP					*/
#define MAPXMIN				MARGELEN
#define MAPXMAX				(MAPXMIN + MAPLENX)
#define MAPYMIN				(HUDYMAX + MARGELEN)
#define MAPYMAX				(MAPYMIN + MAPLENY)

/*					PRINTHUD					*/
#define INHUDX				(x >= HUDXMIN && x < HUDXMAX)
#define INHUDY				(y >= HUDYMIN && y < HUDYMAX)
#define INHUD				(INHUDX && INHUDY)

/*					PRINTMAP					*/
#define INMAPX				(x >= MAPXMIN && x < MAPXMAX)
#define INMAPY				(y >= MAPYMIN && y < MAPYMAX)
#define INMAP				(INMAPX && INMAPY)

/*					COLORS						*/
#define COLOR_BACK			0x00444862	/* VIOLET FONCÉ	*/
#define COLOR_HUD			0x006a4444	/* GRIS CLAIR	*/
#define COLOR_MAP			0x006a4444	/* GRIS CLAIR	*/
#define COLOR_PLAYER		0x000099ff
#define COLOR_ENNEMY		0x00ff0000
#define COLOR_FRONT			0x00ffcc00
#define COLOR_NEXT_PLAYER	0x00cceeff
#define COLOR_NEXT_ENNEMY	0x00660000

void	init_window(t_filler *f)
{
	int		x;
	int		y;

	f->mlx = mlx_init();
	f->window = mlx_new_window(f->mlx, WINLENX, WINLENY, "Filler");
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
}

void	print_point(t_filler *f, int x, int y, int8_t type)
{
	const int color[5] = {COLOR_PLAYER, COLOR_ENNEMY, COLOR_NEXT_ENNEMY, COLOR_FRONT, COLOR_NEXT_PLAYER};
	int i;
	int j;

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
	int i;
	int j;


	j = HUDYMIN;
	while (++j < HUDYMAX - 1)
	{
		i = HUDXMIN;
		while (++i < HUDXMAX - 1)
		{
			if (i == (HUDLENX / 2) + HUDXMIN && i == ((HUDLENX + 1) / 2) + HUDXMIN)
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_FRONT);
			else if (i < HUDXMIN + (f->player_territory * HUDLENX) / (f->xmax * f->ymax))
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_PLAYER);
			else if (i < HUDXMIN + (f->territory * HUDLENX) / (f->xmax * f->ymax))
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_NEXT_PLAYER);
			else if (i >= HUDXMAX - (f->ennemy_territory * HUDLENX) / (f->xmax * f->ymax) - 1)
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_ENNEMY);
			else
				mlx_pixel_put(f->mlx, f->window, i, j, COLOR_NEXT_ENNEMY);
		}
	}
}






