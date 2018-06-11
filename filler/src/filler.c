/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:35:36 by mconti            #+#    #+#             */
/*   Updated: 2018/05/18 18:02:33 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int8_t	build_piece(t_filler *f, char **line)
{
	char	*pos;
	int		r;

	get_next_line(0, line);
	if (f->piece.tab)
		f->piece.tab = (char**)ft_tabdel((void**)f->piece.tab, f->piece.ymax);
	if (ft_strncmp(*line, "Piece ", 6) != 0)
		return (ERROR);
	pos = ft_strchr(*line, ' ') + 1;
	if (!(ft_isdigit(*pos)))
		return (ERROR);
	f->piece.ymax = ft_atoi(pos);
	pos = ft_strchr(pos, ' ') + 1;
	if (!(ft_isdigit(*pos)))
		return (ERROR);
	f->piece.xmax = ft_atoi(pos);
	if (!(f->piece.tab = (char**)malloc(sizeof(char*) * f->piece.ymax)))
		return (ERROR);
	r = RESET;
	ft_strdel(line);
	while (++r < f->piece.ymax)
		get_next_line(0, &(f->piece.tab[r]));
	return (SUCCESS);
}

int8_t	init_free_tab(t_filler *f, char *line)
{
	int i;

	if (!(f->tab))
	{
		if (!(f->tab = (char**)malloc(sizeof(char*) * f->ymax)))
			return (ERROR);
	}
	else
	{
		i = 0;
		while (i < f->ymax)
		{
			ft_strdel(&(f->tab[i]));
			i++;
		}
	}
	get_next_line(0, &line);
	ft_strdel(&line);
	return (SUCCESS);
}

int8_t	parse_tab(t_filler *f, char *line)
{
	int		row;
	char	**tab;

	init_turn(f);
	if (!f->player)
		if (parse_first_time(f, line))
			return (ERROR);
	if (init_free_tab(f, line))
		return (ERROR);
	row = RESET;
	while (++row < f->ymax)
	{
		get_next_line(0, &line);
		if (!(tab = ft_strsplit(line, ' ')))
			return (ERROR);
		ft_strdel(&line);
		if (ft_atoi(tab[0]) != row || tab[2])
			return (ERROR);
		f->tab[row] = tab[1];
		ft_tabdel((void**)tab, 1);
	}
	if (!f->frontier)
		set_frontier(f);
	update_frontier(f, -1);
	return (SUCCESS);
}

int		free_all(t_filler *f)
{
	ft_tabdel((void**)f->piece.tab, f->piece.ymax);
	ft_tabdel((void**)f->frontier, f->ymax);
	ft_tabdel((void**)f->tab, f->ymax);
	ft_printf("0 0\n");
	return (SUCCESS);
}

int		main(void)
{
	char		*line;
	t_filler	f;
	int16_t		n;

	init_filler(&f);
	n = 1;
	while (n)
	{
		if (parse_tab(&f, line))
			return (ERROR);
		if (VISUAL == ON)
			print_hud(&f);
		if (build_piece(&f, &line))
			return (ERROR);
		if ((n = best_placement(&f, 0)))
		{
			ft_printf("%i %i\n", f.bestpos.y, f.bestpos.x);
			update_frontier(&f, 1);
			while (get_next_line(0, &line) == 0)
				;
			ft_strdel(&line);
		}
	}
	return (free_all(&f));
}
