#include "lem_in.h"

t_road      *new_road(t_anthill *ant, int len_road)
{
	t_road *new_road;

	if (!(new_road = (t_road*)malloc(sizeof(t_road))))
		error(MALLOC_ERROR);
	new_road->next = NULL;
	if (!(new_road->rooms = ft_memalloc(sizeof(int) * len_road)))
		error(MALLOC_ERROR);
	new_road->rooms[0] = ant->start;
	new_road->len = len_road;
	return (new_road);
}

int		dijkstra(t_anthill *ant, int road_to_build)
{
	t_queue	*q;
	int		i;
	int		*visited;
	int		len_road;

	len_road = 0;
	if (!(visited = (int*)ft_memalloc(sizeof(int) * ant->nb_room)) ||
		!(ant->path.prev_room = (int*)ft_memalloc(sizeof(int) * ant->nb_room)))
		error(MALLOC_ERROR);
	q = create_queue(ant->start);
	while (q && q->room != ant->end)
	{
		i = RESET_COUNT;
		len_road++;
		while (++i < ant->hill[q->room].nb_links)
		{
			if (ant->hill[q->room].links[i] == ant->end)
			{
				ant->path.prev_room[ant->end] = q->room;
				q = NULL; //je sais pas si c'est necessaire
				break ;
			}
		ft_printf("len: %d, q room: %d, i:%d, q link[i]:%i, road_to_build:%i\n",
				len_road, q->room, i, ant->hill[q->room].links[i], road_to_build);
			if ((ant->hill[ant->hill[q->room].links[i]].route_number == road_to_build)
					&& (!visited[ant->hill[q->room].links[i]]))
			{
				ft_printf("now I add %s to %d in route %d\n", ant->hill[ant->hill[q->room].links[i]].name, q->room, road_to_build);
				add_to_queue(q, ant->hill[q->room].links[i]);
				visited[ant->hill[q->room].links[i]] = 1;
				ant->path.prev_room[ant->hill[q->room].links[i]] = q->room;
			}
		}
		if (q)
			q = next_element(q);
	}
	free(visited);
	return (len_road);
}

t_road	*build_road(t_anthill *ant, t_road *r)
{
	int	i;

	i = r->len;
	while (--i >= 0)
	{
		if (i == r->len - 1)
			r->rooms[i] = ant->end;
		else
			r->rooms[i] = ant->path.prev_room[r->rooms[i + 1]];
	}	
	free(ant->path.prev_room);
	return (r);
}

void	build_fastest_roads(t_anthill *ant)
{
	int i;
	
	if (ant->nmax_road == 1)
		ant->road = build_road(ant, new_road(ant, dijkstra(ant, 0)));
	else
	{
		i = RESET_COUNT;
		while (++i < ant->nmax_road)
		{
			if (ant->finished_roads[i])
			{
				if (i == 0)
					ant->road = build_road(ant, new_road(ant, dijkstra(ant, 1)));
				else
					ant->road->next =
						build_road(ant, new_road(ant, dijkstra(ant, i + 1)));
			}
		}
	}
	show_roads(ant);
}
