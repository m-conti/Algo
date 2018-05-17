#include "filler.h"
// STRATEGIE REMPLISSAGE || CHECK CONTACT

int16_t	check_contact(t_filler *f)
{
	int i;
	int j;
	int b;

	j = 0;
	b = 0;
	while (j < f->piece.ymax && !(i = 0))
	{
		while (i < f->piece.xmax)
		{
			if (f->piece.tab[j][i] == '*')
				{
					if (f->tab[f->piece.y + j + 1][f->piece.x + i] == '.')
						b++;
					if (f->tab[f->piece.y + j - 1][f->piece.x + i] == '.')
						b++;
					if (f->tab[f->piece.y + j][f->piece.x + i + 1] == '.')
						b++;
					if (f->tab[f->piece.y + j][f->piece.x + i - 1] == '.')
						b++;
				}
			i++;
		}
		j++;
	}
	return (b);
}


int8_t	check_piece_pos(t_filler *f, int x1, int y1)
{
	int x2;
	int y2;

	if (x1 < 0 || x1 >= f->xmax || y1 < 0 || y1 >= f->ymax)
		return (0);
	if (f->tab[y1][x1] != '.')
		return (f->tab[y1][x1] == f->player ? 1 : -1);
	x2 = x1 - f->piece.x;
	y2 = y1 - f->piece.y;
	if (x2 < 0 || x2 >= f->piece.xmax || y2 < 0 || y2 >= f->piece.ymax)
		return (0);
	return(f->piece.tab[y2][x2] == '*');
}

// area vaudra 0 => 1 => -1
int8_t	check_for_pos(t_filler *f, int x1, int y1, uint8_t opt)
{
	int8_t		area;

	area = 0;
	if (!(opt & 2))
	{
		while (x1 != f->x)
		{
			area |= check_piece_pos(f, x1, y1);
			x1 += (opt & 1) ? -1 : 1;
			y1 += (opt & 1) ? 1 : -1;
		}
	}
	else
	{
		while (y1 != f->y)
		{
			area |= check_piece_pos(f, x1, y1);
			y1 += (opt & 1) ? -1 : 1;
			x1 += (opt & 1) ? -1 : 1;
		}
	}
	area |= check_piece_pos(f, x1, y1);
	return (area);
}

// STRATEGIE AGRESSION || CHECK AIR DE LA PIECE

int8_t	shortest_distance(t_filler *f)
{
	int			x;
	int			y;
	int16_t		distance;
	int8_t		area;
	uint8_t		opt;

	distance = 0;
	area = 0;
	while (++distance)
	{
		opt = 0;
		while (opt < 4)
		{
			x = f->x;
			y = f->y;
			if (!(opt & 2))
				x += (opt & 1) ? distance : -distance;
			else
				y += (opt & 1) ? distance : -distance;
			area |= check_for_pos(f, x, y, opt++);
		}
		if (area)
			return (area == 1);
	}
	return (0);
}

int16_t	check_area(t_filler *f)
{
	int16_t area;

	area = 0;
	f->y = 0;
	while (f->y < f->ymax)
	{
		f->x = 0;
		while (f->x < f->xmax)
		{
			if (f->tab[f->y][f->x] != '.')
				area += (f->tab[f->y][f->x] == f->player);
			else
				area += (shortest_distance(f) > 0);
			f->x++;
		}
		f->y++;
	}
	return (area);
}

int8_t	check_placement(t_filler *f)
{
	int i;
	int j;
	int b;

	j = 0;
	b = 0;
	while (j < f->piece.ymax && !(i = 0))
	{
		while (i < f->piece.xmax)
		{
			if (f->piece.tab[j][i] == '*')
			{
				if (f->tab[f->piece.y + j][f->piece.x + i] == f->player)
					b++;
				else if (f->tab[f->piece.y + j][f->piece.x + i] != '.')
					return (0);
			}
			if (b > 1)
				return (0);
			i++;
		}
		j++;
	}
	return (b == 1);
}
// CHECK PLACEMENT POS PIECE

void	best_placement(t_filler *f)
{
	int16_t n;

	n = 0;
	while (f->piece.y + f->piece.ymax <= f->ymax)
	{
		f->piece.x = 0;
		while (f->piece.x + f->piece.xmax <= f->xmax)
		{
			if (check_placement(f))
				if ((n = f->tactic[f->strategy](f)) > f->bestpos.n)
				{
					f->bestpos.n = n;
					f->bestpos.x = f->piece.x;
					f->bestpos.y = f->piece.y;
				}
			f->piece.x++;
		}
		f->piece.y++;
	}
}
