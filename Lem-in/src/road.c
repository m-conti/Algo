#include "lem_in.h"

void    calc_nmax_road(t_anthill *ant)
{
	int max;

	if (!(ant->path.distance = (int*)ft_memalloc(sizeof(int) * ant->nb_room)) ||
			!(ant->path.prev_room = (int*)ft_memalloc(sizeof(int) * ant->nb_room)))
		error(MALLOC_ERROR);
	max = ant->nb_ant;
	if (ant->hill[ant->start].nb_links < max)
		max = ant->hill[ant->start].nb_links;
	if (ant->hill[ant->end].nb_links < max)
		max = ant->hill[ant->end].nb_links;
	ant->nmax_road = max;
	ft_printf("nb_ant: %d\nstart nb links:%d\n end nb links: %d\nmax: %d\nstart: %d\nend: %d\n",ant->nb_ant, ant->hill[ant->start].nb_links, ant->hill[ant->end].nb_links, max, ant->start, ant->end);
	if (max < 1)
		error(NO_ESCAPE);
}

t_road      *new_road(t_anthill *ant, int len_road)
{
	t_road *new_road;

	if (!(new_road = (t_road*)ft_memalloc(sizeof(t_road))))
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

	if (!(visited = (int*)ft_memalloc(sizeof(int) * ant->nb_room)) ||
			!(ant->path.prev_room = (int*)ft_memalloc(sizeof(int) * ant->nb_room)))
		error(MALLOC_ERROR);
	q = create_queue(ant->start);
	while (q && q->room != ant->end)
	{
		i = RESET_COUNT;
		len_road = ant->hill[q->room].len_from_start;
		while (++i < ant->hill[q->room].nb_links)
		{
			if (ant->hill[q->room].links[i] == ant->end)
			{
				ant->path.prev_room[ant->end] = q->room;
				ft_memdel((void**)&q); //je sais pas si c'est necessaire
				break ;
			}
			if ((ant->hill[ant->hill[q->room].links[i]].route_number == road_to_build)
					&& (!visited[ant->hill[q->room].links[i]]))
			{
				ant->hill[ant->hill[q->room].links[i]].len_from_start = len_road + 1;
				add_to_queue(q, ant->hill[q->room].links[i]);
				visited[ant->hill[q->room].links[i]] = 1;
				ant->path.prev_room[ant->hill[q->room].links[i]] = q->room;
			}
		}
		if (q)
			q = next_element(q);
	}
	free(visited);
	return (len_road + 1);
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
	t_road	*road;
	int		tmp;

	road = NULL;
	tmp = 0;
	if (ant->nmax_road == 1 && ++tmp)
		ant->road = build_road(ant, new_road(ant, dijkstra(ant, 0)));
	else
	{
		i = RESET_COUNT;
		while (++i < ant->n_roads)
		{
			if (ant->finished_roads[i])
			{
				tmp++;
				if (!road)
				{
					ant->road = build_road(ant, new_road(ant, dijkstra(ant, i + 1)));
					road = ant->road;
				}
				else if ((road->next =
						build_road(ant, new_road(ant, dijkstra(ant, i + 1)))))
					road = road->next;
			}
		}
	}
	ant->n_roads = tmp;
	show_roads(ant);
}
