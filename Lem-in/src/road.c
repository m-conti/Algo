#include "lem_in.h"

void	calc_nmax_road(t_anthill *ant)
{
	int	max;

	if (!(ant->path.distance = (int*)ft_memalloc(sizeof(int) * ant->nb_room)) ||
		!(ant->path.prev_room = (int*)ft_memalloc(sizeof(int) * ant->nb_room)))
		error(MALLOC_ERROR);
	max = ant->nb_ant;
	if (ant->hill[ant->start].nb_links < max)
		max = ant->hill[ant->start].nb_links;
	if (ant->hill[ant->end].nb_links < max)
		max = ant->hill[ant->end].nb_links;
	ant->nmax_road = max;
	if (max < 1)
		error(NO_ESCAPE);
}

void	add_to_queue(t_queue *q, int content)
{
	t_queue *queue;

	queue = q;
	while (queue->next)
		queue = queue->next;
	if (!(queue->next = (t_queue*)malloc(sizeof(t_queue))))
		error(MALLOC_ERROR);
	queue->next->room = content;
	queue->next->next = NULL;
}

t_queue	*next_element(t_queue *q)
{
	t_queue	*tmp;

	tmp = q->next;
	free(q);
	return (tmp);
}

t_queue	*create_queue(int content)
{
	t_queue	*queue;

	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		error(MALLOC_ERROR);
	queue->room = content;
	queue->next = NULL;
	return (queue);
}

t_queue	*path_room(t_anthill *ant, t_queue *rooms_to_check)
{
	t_room	*room;
	int		nb_room;
	int		i;

	nb_room = rooms_to_check->room;
	room = &ant->hill[nb_room];
	i = RESET_COUNT;
	while (++i < room->nb_links)
	{
		if (room->links[i] != ant->start &&
			!ant->path.distance[room->links[i]] &&
			!ant->hill[room->links[i]].occupied)
		{
			ant->path.distance[room->links[i]] = ant->path.distance[nb_room] + 1;
			ant->path.prev_room[room->links[i]] = nb_room;
			add_to_queue(rooms_to_check, room->links[i]);
		}
	}
	return (next_element(rooms_to_check));
}

void	add_road(t_anthill *ant, t_road *road)
{
	t_road	*to_end;

	to_end = ant->road;
	while (to_end->next)
		to_end = to_end->next;
	to_end->next = road;
}

void	find_road(t_anthill *ant)
{
	t_queue	*rooms_to_check;

	rooms_to_check = create_queue(ant->start);
	while (rooms_to_check)
		rooms_to_check = path_room(ant, rooms_to_check);
}

void		set_occupied(t_anthill *ant, int room)
{
	if (room != ant->end)
		ant->hill[room].occupied = 1;
}

t_road		*make_road(t_anthill *ant, int check)
{
	int		room;
	t_road	*road;
	int		i;

	if (!(ant->path.distance[ant->end]))
		return (NULL);
	if (!(road = (t_road*)malloc(sizeof(t_road))))
		error(MALLOC_ERROR);
	road->len = ant->path.distance[ant->end];
	road->check = check;
	if (!(road->rooms = (int*)malloc(sizeof(int) * road->len + 1)))
		error(MALLOC_ERROR);
	room = ant->path.prev_room[ant->end];
	i = 0;
	while (room != ant->start)
	{
		road->rooms[i++] = room;
		set_occupied(ant, room);
		room = ant->path.prev_room[room];
	}
	return (road);
}
