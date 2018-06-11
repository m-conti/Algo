/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:01:33 by mconti            #+#    #+#             */
/*   Updated: 2018/05/25 01:46:22 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

char	*g_block_player[23] =
{
	"10 10 2 1 ",
	"  c #0080EE",
	". c #18B0FF",
	"         .",
	".       . ",
	"..     .  ",
	"...   .   ",
	".... .    ",
	".....     ",
	"....      ",
	"...    .  ",
	"..      . ",
	".       ..",
};

char	*g_block_ennemy[23] =
{
	"10 10 2 1 ",
	"  c #F00000",
	". c #B00000",
	"         .",
	".       . ",
	"..     .  ",
	"...   .   ",
	".... .    ",
	".....     ",
	"....      ",
	"...    .  ",
	"..      . ",
	".       ..",
};

char	*g_block_near_ennemy[23] =
{
	"10 10 2 1 ",
	"  c #520000",
	". c #720000",
	"         .",
	".       . ",
	"..     .  ",
	"...   .   ",
	".... .    ",
	".....     ",
	"....      ",
	"...    .  ",
	"..      . ",
	".       ..",
};

char	*g_block_near_player[23] =
{
	"10 10 2 1 ",
	"  c #CCEEFF",
	". c #A0DDFF",
	"         .",
	".       . ",
	"..     .  ",
	"...   .   ",
	".... .    ",
	".....     ",
	"....      ",
	"...    .  ",
	"..      . ",
	".       ..",
};

char	*g_block_frontier[23] =
{
	"10 10 2 1 ",
	"  c #FFB800",
	". c #FFCC00",
	"         .",
	".       . ",
	"..     .  ",
	"...   .   ",
	".... .    ",
	".....     ",
	"....      ",
	"...    .  ",
	"..      . ",
	".       ..",
};

# define X 1
# define O 2
# define D 3
# define S 4
# define Y 5

uint8_t	g_filler_head[8][45] =
{
	{Y, Y, Y, Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Y, Y, Y, S, 0, 0, 0, 0, 0, 0, 0, 0, 0, D, D, D, D, D, D, D, 0, 0, 0, 0, 0, 0, 0},
	{Y, 0, 0, 0, 0, 0, Y, 0, Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{Y, 0, 0, 0, X, 0, Y, 0, Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, Y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, D, 0, O, 0, 0, 0, 0, 0, 0, 0, 0},
	{Y, Y, Y, 0, 0, 0, Y, 0, Y, 0, 0, Y, 0, 0, 0, Y, S, 0, S, S, D, 0, 0, D, D, 0, 0, D, 0, 0, D, D, 0, 0, D, 0, 0, 0, 0, D, 0, 0, 0, D, D},
	{Y, 0, 0, 0, Y, 0, Y, 0, Y, 0, Y, 0, Y, 0, Y, 0, 0, 0, D, 0, 0, 0, D, 0, 0, 0, D, 0, D, 0, D, 0, D, 0, D, 0, D, 0, D, 0, D, 0, D, 0, 0},
	{Y, 0, 0, 0, Y, 0, Y, 0, Y, 0, Y, Y, 0, 0, S, 0, 0, 0, D, 0, 0, 0, D, 0, 0, 0, D, 0, D, 0, D, 0, D, 0, D, 0, D, 0, D, D, 0, 0, D, 0, 0},
	{Y, 0, 0, 0, Y, 0, Y, 0, Y, 0, Y, 0, 0, 0, S, 0, 0, 0, D, 0, 0, 0, D, 0, 0, 0, D, 0, D, 0, D, 0, D, 0, D, 0, D, 0, D, 0, 0, 0, D, 0, 0},
	{Y, 0, 0, 0, Y, 0, Y, 0, Y, 0, 0, Y, Y, 0, D, 0, 0, 0, D, 0, 0, 0, D, 0, 0, 0, 0, D, 0, 0, D, 0, D, 0, D, 0, D, 0, 0, D, D, 0, D, 0, 0},
};

#endif
