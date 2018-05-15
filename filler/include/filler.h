#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include "../libft/libft.h"
# define PLAYER_NAME "timmy.filler" //

typedef struct	s_piece
{
	int			nrow;
	int			ncol;
	char		**piece;
}				t_piece;

typedef struct	s_filler
{
	char		player;
	char		ennemy;
	int			strategy;
	int			xmax;
	int			ymax;
	char		**tab;
}				t_filler;


#endif
