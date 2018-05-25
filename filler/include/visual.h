/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 04:27:00 by mconti            #+#    #+#             */
/*   Updated: 2018/05/25 04:27:02 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <mlx.h>

/*
**					BLOCK
*/
# define BLCX				&f->img_len[0]
# define BLCY				&f->img_len[1]

/*
**				LENGHT ANNEXE
*/
# define MARGELEN			40
# define POINTLEN			10
# define MARGECASE			1
# define CASELEN			(POINTLEN + MARGECASE)
# define NBCASES			(f->xmax * f->ymax)

/*
**					POS NAMES
*/
# define ENAME				"Ennemy"
# define NAMEPX				HUDXMIN - 20
# define NAMEEX				HUDXMAX - 40
# define VSX				HUDXMIN + (HUDLENX / 2) - 10
# define NAMESY				HUDYMIN - (MARGELEN / 2)

/*
**					LENGHT MAP
*/
# define MAPLENY			(f->ymax * CASELEN + MARGECASE)
# define MAPLENX			(f->xmax * CASELEN + MARGECASE)

/*
**					LENGHT HUD
*/
# define HUDLENY			40
# define HUDLENX			(MAPLENX - MARGELEN)

/*
**					LENGHT WINDOW
*/
# define WINLENY			(MAPYMAX + MARGELEN)
# define WINLENX			(MAPXMAX + MARGELEN)

/*
**					POS HUD
*/
# define HUDXMIN			((3 * MARGELEN) / 2)
# define HUDXMAX			(HUDXMIN + HUDLENX)
# define HUDYMIN			(HEADYMAX + MARGELEN)
# define HUDYMAX			(HUDYMIN + HUDLENY)

/*
**					POS MAP
*/
# define MAPXMIN			MARGELEN
# define MAPXMAX			(MAPXMIN + MAPLENX)
# define MAPYMIN			(HUDYMAX + MARGELEN)
# define MAPYMAX			(MAPYMIN + MAPLENY)

/*
**					PRINT HUD
*/
# define INHUDX				(x >= HUDXMIN && x < HUDXMAX)
# define INHUDY				(y >= HUDYMIN && y < HUDYMAX)
# define INHUD				(INHUDX && INHUDY)

/*
**					PRINT MAP
*/
# define INMAPX				(x >= MAPXMIN && x < MAPXMAX)
# define INMAPY				(y >= MAPYMIN && y < MAPYMAX)
# define INMAP				(INMAPX && INMAPY)

/*
**					HEADER
*/
# define HEADNB				(f->xmax >= 38 ? 45 : 17)
# define HEADLENX			(HEADNB * CASELEN)
# define HEADLENY			(8 * CASELEN)
# define HEADXMIN			(MAPXMIN + MAPLENX / 2) - (HEADLENX / 2)
# define HEADXMAX			(MAPXMIN + MAPLENX / 2) + (HEADLENX / 2)
# define HEADYMIN			(MARGELEN / 2)
# define HEADYMAX			(HEADYMIN + HEADLENY)

/*
**					COLORS
*/
# define COLOR_BACK			0x00444862
# define COLOR_HUD			0x00777777
# define COLOR_MAP			0x00777777
# define COLOR_PLAYER		0x000099ff
# define COLOR_ENNEMY		0x00ff0000
# define COLOR_FRONT		0x00ffcc00
# define COLOR_NEXT_PLAYER	0x00cceeff
# define COLOR_NEXT_ENNEMY	0x00660000

#endif
