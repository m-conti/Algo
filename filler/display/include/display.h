/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:07:04 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/23 17:31:20 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <mlx.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"

// keys
# define ESC_KEY 53
# define LEFT_ARROW_KEY 123
# define RIGHT_ARROW_KEY 124

// colors
# define BLUE 0xFF
# define GREEN 0xFF00
# define RED 0xFF0000
# define DARK_GRAY 0x111111
# define WHITE 0xFFFFFF
# define PLAYER_COLOR 0x40A3FB
# define CHALLENGER_COLOR 0xF09042

# define TEXT_COLOR WHITE

//params
# define WIN_HEIGHT 1200
# define WIN_WIDTH 1000
# define WIN_TITLE "Filler display"

# define SQ_SIZE 10

# define Y_PLAYER_NAME 20
# define X_PLAYER_NAME 40
# define X_CHALLENGER_NAME 800
# define Y_TURN WIN_WIDTH/2 - 40
# define X_TURN 1100


typedef struct	s_display_mlx
{
	void		*mlx;
	void		*win;
	int			sq_size;
	int			fd;
	int			player;
	int			xmax;
	int			ymax;
	char		**tab;
	char		**frontier;
}				t_display_mlx;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

#endif
