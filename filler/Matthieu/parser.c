
// STRATEGIE REMPLISSAGE || CHECK CONTACT

int16_t	check_contact(t_filler p)
{
	int i;
	int j;
	int b;

	j = 0;
	b = 0;
	while (j < p.piece.ymax && !(i = 0))
	{
		while (i < p.piece.xmax)
		{
			if (p.piece.tab[j][i] == '*')
				{
					if (p.tab[p.piece.y + j + 1][p.piece.x + i] == '.')
						b++;
					if (p.tab[p.piece.y + j - 1][p.piece.x + i] == '.')
						b++;
					if (p.tab[p.piece.y + j][p.piece.x + i + 1] == '.')
						b++;
					if (p.tab[p.piece.y + j][p.piece.x + i - 1] == '.')
						b++;
				}
			i++;
		}
		j++;
	}
	return (b);
}

// STRATEGIE AGRESSION || CHECK AIR DE LA PIECE

int8_t	shortest_distance(t_filler p)
{
	int			x1;
	int			y1;
	int16_t		distance;
	int8_t		area;

	distance = 0;
	area = 0;
	while ((++distance) >= 0)
	{
		i = 0;
		while (i < 4)
		{
			x1 = p.x;
			y1 = p.y;
			if (!(i & 2))
				x1 += opt & 1 ? distance : -distance;
			else
				y1 += opt & 1 ? distance : -distance;
			area |= check_for_pos(p, x, y, i++);
		}
		if (area)
			return (area);
	}
}

int8_t	check_piece_pos(t_filler p, int x1, int y1)
{
	int x2;
	int y2;

	if (x1 < 0 || x1 >= p.xmax || y1 < 0 || y1 >= p.ymax)
		return (0);
	if (p.tab[y1][x1] != '.')
		return (tab[y1][x1] == p.ennemy ? -1 : 1);
	x2 = x1 - p.piece.x;
	y2 = y1 - p.piece.y;
	if (x2 < 0 || x2 >= p.piece.xmax || y2 < 0 || y2 >= p.piece.ymax)
		return (0);
	return(p.piece.piece[y2][x2] == '*' ? 1 : 0);
}

int8_t	check_for_pos(t_filler p, int x1, int y1, uint8_t opt)
{
	int8_t		area;

	area = 0;
	if (!(opt & 2))
	{
		while (x1 != p.x)
		{
			area |= check_piece_pos(p, x1, y1);
			x1 += opt & 1 ? -1 : 1;
			y1 += opt & 1 ? 1 : -1;
		}
	}
	else
	{
		while (y1 != p.y)
		{
			area |= check_piece_pos(p, x1, y1);
			y1 += opt & 1 ? -1 : 1;
			x1 += opt & 1 ? -1 : 1;
		}
	}
	return (area);
}

int16_t	check_area(t_filler p)
{
	int16_t area;

	p.y = 0;
	while (p.y < p.ymax)
	{
		p.x = 0;
		while (p.x < p.xmax)
		{
			if (p.tab[p.y][p.x] != '.')
				area += tab[p.y][p.x] == p.ennemy ? 0 : 1;
			area += shortest_distance(p) > 0 ? 1 : 0;
			p.x++;
		}
		p.y++;
	}
	return (area);
}

// CHECK PLACEMENT POS PIECE

void	best_placement(t_filler *p)
{
	int16_t n;

	p->piece.x = 0;
	p->piece.y = 0;
	while (p->piece.y + p->piece.ymax <= p->ymax)
	{
		while (p->piece.x + p->piece.xmax <= p->xmax)
		{
			if (check_placement(p))
				if ((n = g_tactic[p->tactic](p)) > p->bestpos.n)
				{
					p->bestpos.n = n;
					p->bestpos.x = p->piece.x;
					p->bestpos.y = p->piece.y;
				}
			p->piece.x++;
		}
		p->piece.y++;
	}
}

int8_t	check_placement(t_filler p)
{
	int i;
	int j;
	int b;

	j = 0;
	b = 0;
	while (j < p.piece.ymax && !(i = 0))
	{
		while (i < p.piece.xmax)
		{
			if (p.piece.tab[j][i] == '*')
				if (p.tab[p.piece.y + j][p.piece.x + i] == '.')
					b++;
			if (b > 1)
				return (0);
			i++;
		}
		j++;
	}
	return (b == 1 ? 1 : 0);
}
