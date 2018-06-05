#include "lem_in.h"


int		still_a_road(t_room *room, t_anthill *ant, int init_rn)
{
	t_queue	*q;
	int		i;
	int	*visited;

	if (!(visited = (int*)ft_memalloc(sizeof(int) * ant->nb_room)))
		error(MALLOC_ERROR);
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
				//Free tous les q...
				room->route_number = init_rn;
				return (1);
			}
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
	free(q); //verif
	free(visited);
	return (0);
}

int		can_overwrite(int orig_route_num, t_room *room, t_anthill *ant)
{
	if ((!(ant->finished_roads[orig_route_num]) && room->route_number > 0 &&
		ant->finished_roads[room->route_number - 1]) &&
		still_a_road(room, ant, room->route_number))
		return (1);
	return (0);
}	

int		propagate(t_room *room, t_anthill *ant)
{
	int		ln;
	int		change;
	t_room	*next;

	change = 0;
	ln = RESET_COUNT;
	if (room->route_number > 0 && room->route_number <= ant->nmax_road)
		while (++ln < room->nb_links)
		{
			next = &ant->hill[room->links[ln]];
			if (((next->route_number == 0)
				|| can_overwrite(room->route_number - 1, next, ant)
				|| (next == &ant->hill[ant->end]))
				&& (!(next == &ant->hill[ant->start]))
				&& !(ant->finished_roads[room->route_number - 1]))
			{
				if (next == &ant->hill[ant->end])
				{
					if (!(ant->finished_roads[room->route_number - 1]))
					{
						ant->finished_roads[room->route_number - 1] = 1; // on peut pas faire ça il faut la mettre ant->finished_road[i] = room->route_number sinon on segfault si on trouve pas les premieres routes;
						change = 1;
					}
				}
				else
				{
					change = 1;
					next->route_number = room->route_number;
				}
			}
		}
	return (change);
}


void	assign_rooms_to_routes(t_anthill* ant)
{
	int i;
	int	change;

	if (ant->nmax_road > 1)
	{
		ant->n_roads = ant->hill[ant->start].nb_links;
		if (!(ant->finished_roads = (int*)ft_memalloc(sizeof(int) * ant->n_roads)))
			error(MALLOC_ERROR);
		i = RESET_COUNT;
		while (++i < ant->n_roads)
			ant->hill[ant->hill[ant->start].links[i]].route_number = i + 1;
		change = 1;
		while (change)
		{
			change = 0;
			i = RESET_COUNT;
			while (++i < ant->nb_room)
			{
				if (propagate(&ant->hill[i], ant))
					change = 1;
			}
		}
		i = RESET_COUNT;
		while (++i < ant->n_roads)
			ft_printf("finished[%i]: %i\n", i, ant->finished_roads[i]);
	}
}

