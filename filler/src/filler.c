/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 14:18:36 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/22 17:05:39 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_turn(t_filler *f)
{
	f->piece.x = 0;
	f->piece.y = 0;
	f->bestpos.score = 0;
}

void	init_filler(t_filler *f)
{
	f->player = '\0';
	f->ennemy = '\0';
	f->error = 0;
	f->piece.tab = NULL;
	f->tab = NULL;
	f->frontier = NULL;
	f->tactic[0] = &update_frontier_test;
	f->tactic[1] = &check_contact;
	f->display = DISPLAY;
	if (f->display)
		f->fd = open("./filler.disp", O_CREAT | O_WRONLY | O_TRUNC);
}	

void	free_tab_content(void **tab, int max)
{
	int i;

	if (tab)
	{
		i = 0;
		while (i < max)
		{
			free(tab[i]);
			i++;
		}
	}
}

void	free_filler(t_filler *f)
{
	if (f->frontier)
	{
		free_tab_content((void**)f->frontier, f->ymax);
		free(f->frontier);
	}
	if (f->tab)
	{
		free_tab_content((void**)f->tab, f->ymax);
		free(f->tab);
	}
}

int main(void)
{
	char		*line;
	t_filler	f;
	int16_t		n;

	init_filler(&f);
	n = 1;
	while (n)
	{	
		init_turn(&f);
		parse_tab(&f);
		if (f.error != 0)
			return (1);
		update_frontier(&f, ENNEMY_TERRITORY);
		build_piece(&f);
		if (f.error != 0)
			return (1);
		if (!(n = best_placement(&f, 0)))
			break ;	
		ft_printf("%i %i\n", f.bestpos.y, f.bestpos.x);
		update_frontier(&f, PLAYER_TERRITORY);
		while (get_next_line(0, &line) == 0)
			;
		ft_strdel(&line); // del line Plateau X X
	}
	free_filler(&f);
	return (0);
}
