
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

void	path_zero(t_anthill *ant)
{
	int		i;

	i = RESET_COUNT;
	while (++i < ant->nb_room)
	{
		ant->path.distance[i] = 0;
		ant->path.prev_room[i] = 0;
	}
}

int		main(void)
{
	t_anthill	ant;

	init_anthill(&ant);
	parse(&ant);
	calc_nmax_road(&ant);

	assign_rooms_to_routes(&ant);
//	show_rooms(&ant);
	
	build_fastest_roads(&ant);
	sorting_roads(&ant);
	int i = -1;
	int j;
	t_road *cur;
	while (++i < ant.n_roads && (cur = &ant.road[i]))
	{
		j = -1;
		while (++j < cur->len)
		{
			if (j == 0)
				ft_printf("%5s", ant.hill[cur->rooms[j]].name);
			else
				ft_printf("->%5s", ant.hill[cur->rooms[j]].name);
		}
		ft_printf(" || %20i", cur->len);
		ft_printf("\n");
	}
	print_solution(&ant);
	//ft_putendl(ant.lines);


	/*
	int i = 0;
	ft_printf("Start: %s\n",ant.hill[ant.start].name);
	ft_printf("End: %s\n",ant.hill[ant.end].name);
	while (i < ant.road->len)
	{
		ft_printf("%s\n",ant.hill[ant.road->rooms[i]].name);
		i++;
	}*/
	return (0);
}
