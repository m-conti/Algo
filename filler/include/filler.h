/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 01:42:15 by mconti            #+#    #+#             */
/*   Updated: 2018/05/25 01:42:17 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <inttypes.h>
# include <limits.h>
# include "ft_printf.h"
# include "visual.h"

# define VISUAL 0

# define PNAME "Mconti"
# define RESET -1
# define ERROR 1
# define SUCCESS 0
# define ON 1
# define TWO_BYTES (0x10)
# define FOUR_BYTES (0x20)
# define SIX_BYTES (0x30)
# define MASQ_SHORT (0xFFFF)
# define Y_PLAYER ((coord >> TWO_BYTES) & MASQ_SHORT)
# define X_PLAYER (coord & MASQ_SHORT)
# define Y_ENNEMY ((coord >> SIX_BYTES) & MASQ_SHORT)
# define X_ENNEMY ((coord >> FOUR_BYTES) & MASQ_SHORT)
# define NEW_PLAYER_TERRITORY (3)
# define NEW_ENNEMY_TERRITORY (-3)
# define LOST_TERRITORY (2)
# define PLAYER_TERRITORY (1)
# define ENNEMY_TERRITORY (-1)
# define UP (y - 1)
# define DOWN (y + 1)
# define RIGHT (x + 1)
# define LEFT (x - 1)

typedef struct	s_piece
{
	int			ymax;
	int			xmax;
	int			x;
	int			y;
	char		**tab;
}				t_piece;

typedef struct	s_bestpos
{
	int			n;
	int			x;
	int			y;
}				t_bestpos;

typedef struct	s_filler
{
	char		player;
	char		ennemy;
	int			xmax;
	int			ymax;
	t_bestpos	bestpos;
	t_piece		piece;
	int16_t		(*tactic[2])(struct s_filler*);
	char		**tab;
	int			fd;
	void		*mlx;
	void		*window;
	int8_t		**frontier;
	int			territory;
	int			player_territory;
	int			ennemy_territory;
	int			img_len[2];
	void		*img_clr[5];
}				t_filler;

typedef struct	s_pos
{
	int			x;
	int			y;
	int			distance;
}				t_pos;

void			init_filler(t_filler *f);
void			init_turn(t_filler *f);
int8_t			parse_first_time(t_filler *f, char *line);
int8_t			plateau_max(t_filler *f, char *line);
int8_t			parse_tab(t_filler *f, char *line);
int8_t			init_free_tab(t_filler *f, char *line);
int8_t			build_piece(t_filler *f, char **line);
int				free_all(t_filler *f);
void			set_frontier(t_filler *f);
int8_t			belongs_to_us(int x, int y, int64_t coord);
void			find_coord(t_filler *f, int64_t *coord);
void			draw_frontier(t_filler *f, int x, int y);
void			draw_print_frontier(t_filler *f);
void			update_frontier(t_filler *f, int player_sign);
int8_t			is_player(t_filler *f, int x, int y, int player_sign);
int8_t			check_pos(t_filler *f, t_pos p, int player_sign);
int8_t			closest_player(t_filler *f, int x, int y, int player_sign);
void			move_next_frontier(t_filler *f, int x, int y, int player_sign);
void			fill_frontier(t_filler *f, int x, int y, int player_sign);
int16_t			update_frontier_test(t_filler *f);
int8_t			is_player_test(t_filler *f, int x, int y);
int8_t			check_pos_test(t_filler *f, t_pos p);
int8_t			closest_player_test(t_filler *f, int x, int y);
int16_t			move_next_frontier_test(t_filler *f, int x, int y, int16_t ret);
int16_t			fill_frontier_test(t_filler *f, int x, int y);
void			init_block(t_filler *f);
void			init_window(t_filler *f);
void			print_block(t_filler *f, int x, int y, int8_t type);
void			print_point(t_filler *f, int x, int y, int8_t type);
void			print_hud(t_filler *f);
int				check_around(t_filler *f, int i, int j, int b);
int16_t			check_contact(t_filler *f);
int8_t			check_placement(t_filler *f);
int16_t			best_placement(t_filler *f, uint8_t strategy);

#endif
