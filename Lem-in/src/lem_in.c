/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:41:27 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/05 19:05:57 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_anthill(t_anthill *ant)
{
	ant->stop = 0;
	ant->hill = NULL;
	if (!(ant->hill = (t_room*)ft_memalloc(sizeof(t_room))))
		error(MALLOC_ERROR);
	ant->hill->name = NULL;
	ant->nb_ant = 0;
	ant->nb_room = 0;
	ant->start = -1;
	ant->end = -1;
	ant->lines = NULL;
	ant->parstatus = NB_ANT_CHECK;
	ant->check_status[NB_ANT_CHECK] = &check_status_nb_ant;
	ant->check_status[ROOM_CHECK] = &check_status_room;
	ant->check_status[TUBE_CHECK] = &check_status_tube;
}

void	add_line_to_print(t_anthill *ant)
{
	if (!(ant->lines = ft_strjoinfree(ant->lines, ant->current_line, 3)))
		error(MALLOC_ERROR);
	if (!(ant->lines = ft_strjoinfree(ant->lines, "\n", 1)))
		error(MALLOC_ERROR);
}

void	parse(t_anthill *ant)
{
	int		ret;

	while (!ant->stop && (ret = get_next_line(0, &(ant->current_line))))
	{
		if (ret == -1)
			error(GNL_ERROR);
		if (!(ant->current_line[0]))
			error(EMPTY_LINE);
		if (ant->current_line[0] != '#')
			ant->check_status[ant->parstatus](ant);
		else if (ant->current_line[1] == '#')
			check_command(ant);
		if (!ant->stop)
			add_line_to_print(ant);
		else
			ft_strdel(&(ant->current_line));
	}
}

void	error(int err_nb)
{
	if (DEBUG)
		ft_printf("Error n %d\n", err_nb);
	ft_printf("ERROR\n");
	exit(1);
}

int		main(void)
{
	t_anthill	ant;

	init_anthill(&ant);
	parse(&ant);
	calc_nmax_road(&ant);
	assign_rooms_to_routes(&ant);
	build_fastest_roads(&ant);
	sorting_roads(&ant);
	ft_putendl(ant.lines);
	print_solution(&ant);
	//free_all()
	return (0);
}
