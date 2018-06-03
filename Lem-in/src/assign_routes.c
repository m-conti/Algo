#include "lem_in.h"


int		still_a_road(t_room *room, t_anthill *ant, int init_rn)
{
	t_queue	*q;
	int		i;

	int	*visited;

	visited = (int*)ft_memalloc(sizeof(int) * ant->nb_room);

	room->route_number = -1;
	q = create_queue(ant->start);
	while (q)
	{
		if (q->room == ant->end)
		{
			free(visited);
			return (1);
		}
		i = RESET_COUNT;
		while (++i < ant->hill[q->room].nb_links)
		{
			if (ant->hill[q->room].links[i] == ant->end)
			{
				free(visited);
				room->route_number = init_rn;
				return (1);
			}
			//ft_printf("room:%d, route_n:%d\n", ant->hill[q->room].links[i], ant->hill[ant->hill[q->room].links[i]].route_number);
			if ((ant->hill[ant->hill[q->room].links[i]].route_number == init_rn)
					&& (!visited[ant->hill[q->room].links[i]]))
			{
				add_to_queue(q, ant->hill[q->room].links[i]);
				visited[ant->hill[q->room].links[i]] = 1;
			}
		}
		q = next_element(q);
	}
	room->route_number = init_rn;
	free(visited);
	return (0);
}

int		can_overwrite(int orig_route_num, t_room *room, t_anthill *ant, int *finished)
{
/*	ft_printf("Can_overwrite call: %i, %i, %i\n",
			!(finished[orig_route]),
			finished[room->route_number - 1],
			still_a_road(room, ant, room->route_number)); */
	if ((!(finished[orig_route_num]) &&
		finished[room->route_number - 1]) &&
		still_a_road(room, ant, room->route_number))
		return (1);
	return (0);
}	

int		propagate(t_room *room, t_anthill *ant, int *finished)
{
	int		ln;
	int		change;
	t_room	*next;

	change = 0;
	ln = RESET_COUNT;
	if (room->route_number > 0)
		while (++ln < room->nb_links)
		{
			next = &ant->hill[room->links[ln]];
			

			 ft_printf("Appel Propagate, try to put route %d in room %d\n", 
				room->route_number, room->links[ln]);
			/*
			 ft_printf("Appel Propagate\ntry to put route: %d in room %d; Conds: %i, %i, %i, %i\n",
				room->route_number, room->links[ln],
				(!next->route_number),
				can_overwrite(room->route_number, next, ant, finished),
				(next == &ant->hill[ant->end]),
				(!(next == &ant->hill[ant->start])));
*/
		
			if (((next->route_number == 0)
				|| can_overwrite(room->route_number - 1, next, ant, finished)
				|| (next == &ant->hill[ant->end]))
				&& (!(next == &ant->hill[ant->start]))
				&& !(finished[room->route_number - 1]))
			{
				if (next == &ant->hill[ant->end])
				{
					if (!(finished[room->route_number -1]))
					{
						finished[room->route_number -1] = 1;
						change = 1;
						ft_printf(": route %d finished\n", room->route_number);
					}
				}
				else
				{
					change = 1;
					next->route_number = room->route_number;
					ft_printf(": success\n");
				}
			}
		}
	return (change);
}


void	assign_rooms_to_routes(t_anthill* ant)
{
	int n_roads;
	int i;
	int	change;
	int	*finished;

	ft_printf("max :%d\n", ant->nmax_road);
	if (ant->nmax_road == 1)
		;//find_fastest_road(ant);
	else
	{
		n_roads = ant->hill[ant->start].nb_links;
		if (!(finished = (int*)ft_memalloc(sizeof(int) * n_roads)))
			error(MALLOC_ERROR);
		i = RESET_COUNT;
		while (++i < n_roads)
			ant->hill[ant->hill[ant->start].links[i]].route_number = i + 1;
		change = 1;
		while (change)
		{
			change = 0;
			i = RESET_COUNT;
			while (++i < ant->nb_room)
			{
				if (propagate(&ant->hill[i], ant, finished))
					change = 1;
			}
		}
		i = RESET_COUNT;
		while (++i < n_roads)
			ft_printf("finished[%i]: %i\n", i, finished[i]);
		free(finished);
	}

}

