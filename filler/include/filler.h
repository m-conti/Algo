#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <inttypes.h>
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
	uint8_t		strategy;
	int			xmax;
	int			ymax;
	int			x;
	int			y;
	t_bestpos	bestpos;
	t_piece		piece;
	int16_t		(*tactic[2])(struct s_filler*);
	char		**tab;
int		fd;
}				t_filler;

int16_t			check_contact(t_filler *f);
int16_t			check_area(t_filler *f);
void			best_placement(t_filler *f);

#endif