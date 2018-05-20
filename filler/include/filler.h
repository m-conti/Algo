#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <inttypes.h>
# include <limits.h>
# include "ft_printf.h"
# define PLAYER_NAME "timmy.filler" //

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

	int8_t		**frontier;
	int			territory;
}				t_filler;

typedef struct	s_pos
{
	int			x;
	int			y;
	int			distance;
}				t_pos;

void			*init_affichage(t_filler *f);
void			update_frontier(t_filler *f, int player_sign);
void			fill_frontier(t_filler *f, int x, int y, int player_sign);
void			set_frontier(t_filler *f);
int16_t			check_contact(t_filler *f);
int16_t			best_placement(t_filler *f, uint8_t strategy);
int16_t			update_frontier_test(t_filler *f);

#endif
