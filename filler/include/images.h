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

#endif