/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 04:56:15 by mconti            #+#    #+#             */
/*   Updated: 2018/05/25 04:56:17 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_turn(t_filler *f)
{
	f->piece.x = 0;
	f->piece.y = 0;
	f->bestpos.n = 0;
	f->player_territory = 0;
	f->ennemy_territory = 0;
}

int8_t	plateau_max(t_filler *f, char *line)
{
	char **plateau_line;

	if (!(plateau_line = ft_strsplit(line, ' ')))
		return (ERROR);
	ft_strdel(&line);
	if (!(plateau_line[1] && plateau_line[2]))
		return (ERROR);
	f->ymax = ft_atoi(plateau_line[1]);
	f->xmax = ft_atoi(plateau_line[2]);
	if (!(f->ymax >= 2 && f->xmax >= 2))
		return (ERROR);
	ft_tabdel((void**)plateau_line, -1);
	return (SUCCESS);
}

void	init_filler(t_filler *f)
{
	f->player = '\0';
	f->territory = 0;
	f->ennemy = '\0';
	f->piece.tab = NULL;
	f->tab = NULL;
	f->frontier = NULL;
	f->tactic[0] = &update_frontier_test;
	f->tactic[1] = &check_contact;
}

int8_t	parse_first_time(t_filler *f, char *line)
{
	if ((get_next_line(0, &line) != 1))
		return (ERROR);
	if (ft_strncmp("$$$ exec p1", line, 11) == 0)
		f->player = 'O';
	else if (ft_strncmp("$$$ exec p2", line, 11) == 0)
		f->player = 'X';
	else
		return (ERROR);
	ft_strdel(&line);
	if ((get_next_line(0, &line) != 1))
		return (ERROR);
	if (ft_strncmp("Plateau ", line, 8) == 0)
	{
		if (plateau_max(f, line))
			return (ERROR);
	}
	else
		return (ERROR);
	return (SUCCESS);
}
