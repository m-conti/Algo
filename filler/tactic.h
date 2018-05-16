
#ifndef TACTIC_H
# define TACTIC_H

//mettre t_piece dans t_plateau

typedef	struct	s_bestpos
{
	int		n;
	int		x;
	int		y;
}				t_bestpos;

int16_t	tactic[2](t_filler) = {&check_area, &check_contact};

#endif