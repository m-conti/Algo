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

#include "mlx.h"
#include "filler.h"
#define RESET -1

/*				TAILLE MARGE			*/
#define MARGELEN 20

/*				TAILLE MAP				*/
#define MAPLENY 1000
#define MAPLENX 1000

/*				TAILLE HUD				*/
#define HUDLENY 200
#define HUDLENX (MAPLENX - 2 * MARGELEN)

/*				TAILLE WINDOW			*/
#define WINLENY (MAPLENY + HUDLENY + 3 * MARGELEN)
#define WINLENX (MAPLENX + 2 * MARGELEN)

/*				POINTS HUD				*/
#define HUDXMIN (2 * MARGELEN)
#define HUDXMAX (HUDXMIN + HUDLENX)
#define HUDYMIN MARGELEN
#define HUDYMAX (HUDYMIN + HUDLENY)

/*				POINTS MAP				*/
#define MAPXMIN MARGELEN
#define MAPXMAX (MAPXMIN + MAPLENX)
#define MAPYMIN (HUDYMAX + MARGELEN)
#define MAPYMAX (MAPYMIN + MAPLENY)

/*				PRINTHUD				*/
#define INHUDX (x >= HUDXMIN && x < HUDXMAX)
#define INHUDY (y >= HUDYMIN && y < HUDYMAX)
#define INHUD (INHUDX && INHUDY)

/*				PRINTMAP				*/
#define INMAPX (x >= MAPXMIN && x < MAPXMAX)
#define INMAPY (y >= MAPYMIN && y < MAPYMAX)
#define INMAP (INMAPX && INMAPY)

/*				COLORS					*/
#define COLOR_BACK 0x00444862	/* VIOLET FONCÉ	*/
#define COLOR_HUD 0x009090a0	/* GRIS CLAIR	*/
#define COLOR_MAP 0x009090a0	/* GRIS CLAIR	*/

void	*init_affichage(t_filler *f)
{
	void	*mlx;
	void	*window;
	int		x;
	int		y;

	(void)f;
	mlx = mlx_init();
	window = mlx_new_window(mlx, WINLENX, WINLENY, "Filler");
	y = RESET;
	while (++y < WINLENY)
	{
		x = RESET;
		while (++x < WINLENX)
		{
			if (INHUD)
				mlx_pixel_put(mlx, window, x, y, COLOR_HUD);
			else if (INMAP)
				mlx_pixel_put(mlx, window, x, y, COLOR_MAP);
			else
				mlx_pixel_put(mlx, window, x, y, COLOR_BACK);
		}
	}
	return (mlx);
}
