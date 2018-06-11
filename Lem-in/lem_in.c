
#include "lem_in.h"

void	init_anthill(t_anthill *ant)
{
	ant->stop = 0;
	ant->hill = NULL;
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
	if (!(ant->lines = ft_joinfree(ant->lines, "\n", FREE_FIRST)))
		error(MALLOC_ERROR);
	if (!(ant->lines = ft_joinfree(ant->lines, ant->current_line, FREE_BOTH)))
		error(MALLOC_ERROR);
}

void	parse(t_anthill *ant)
{
	int		ret;

	while (!ant->stop && (ret = get_next_line(0, &ant->current_line)))
	{
		if (ret == -1)
			error(GNL_ERROR);
		if (!ant->currentline[0])
			error(EMPTY_LINE);
		if (ant->current_line[0] != '#')
			ant->check_status[ant->parstatus](ant);
		else if (ant->current_line[1] == '#')
			check_command(ant);
		if (!ant->stop)
			add_line_to_print(ant);
		else
			ft_strdel(&line);
	}
}

void	path_zero(t_anthill ant)
{
	int		i;

	i = RESET_COUNT;
	while (++i < ant->nb_room)
	{
		ant->path.distance[i] = 0;
		ant->path.prev_room[i] = 0;
	}
}

void	build_roads(t_anthill *ant)
{
	int		n;
	t_road	*road;

	find_road(ant);
	if (!(road = make_road(ant, n)))
		error(NO_ESCAPE);
	ant->road = road;
	n = 1;
	while (road && n < ant->nmax_road)
	{
		path_zero(ant);
		find_road(ant);
		if (road = make_road(ant, n))
		{
			add_road(ant, road);
			n++;
		}
	}
	ant->nmax_road = n;
	free(ant->path.distance);
	free(ant->path.prev_room);
}

int		main(void)
{
	t_anthill	ant;

	init_anthill(&ant);
	parse(&ant);
	calc_nmax_road(&ant);
	build_road(&ant);
	ft_putendl(ant.lines);

	return (0);
}