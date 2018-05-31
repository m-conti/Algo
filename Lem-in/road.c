#include "lem_in.c"

void	calc_nmax_road(t_anthill *ant)
{
	int	max;

	max = ant->nb_ant;
	if (ant->hill[ant->start].nb_links < max)
		max = ant->hill[ant->start].nb_links;
	if (ant->hill[ant->end].nb_links < max)
		max = ant->hill[ant->end].nb_links;
	ant->nmax_road = max;
	if (max < 1)
		error(NO_ESCAPE)
}

void	add_to_queue(t_queue *q, int content)
{
	t_queue *queue;

	queue = q;
	while (queue->next)
		queue = queue->next;
	if (!(queue->next = (t_queue*)malloc(sizeof(t_queue))))
		error(MALLOC_ERROR);
	queue->next->d = content;
	queue->next->next = NULL;
}

void	next_element(t_queue *q)
{
	t_queue	*tmp;

	tmp = q->next;
	free(q);
	q = tmp;
}

t_queue	*create_queue(int content)
{
	t_queue	*queue;

	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		error(MALLOC_ERROR);
	queue->d = content;
	queue->next = NULL;
	return (queue);
}

void	find_road(t_anthill *ant)
{
	int		i;
	int		nb_room;
	t_room	*room;
	t_queue	*rooms_to_check;

	rooms_to_check = create_queue(ant->start);
	while (rooms_to_check && (nb_room = rooms_to_check->d) != -1)
	{
		room = ant->hill[nb_room];
		i = RESET_COUNT;
		while (++i < room->nb_links)
		{
			if (room->links[i] != ant->start &&
				((ant->path.distance[room->links[i]] >
				ant->path.distance[nb_room] + 1) ||
				!ant->path.distance[room->links[i]]) &&
				!ant->hill[room->links[i]].occupied)
			{
				ant->path.distance[room->links[i]] = ant->path.distance[nb_room] + 1;
				ant->path.prev_room[room->links[i]] = nb_room;
				add_to_queue(rooms_to_check, room->links[i]);
			}
		}
		next_element(rooms_to_check);
	}
}

t_road		*make_road(t_anthill *ant)
{
	int		room;
	t_road	*road;
	int		i;

	if (!(road = (t_road*)malloc(sizeof(t_road))))
		error(MALLOC_ERROR);
	if (!(road->len = ant->path.distance[ant->end]))
		return (NULL); //BON COURAGE !!!
	if (!(road->rooms = (int*)malloc(sizeof(int) * ant->path.distance[ant->end] + 1)))
		error(MALLOC_ERROR);
	room = ant->path.prev_room[ant->end];
	i = 0;
	while (room != ant->start)
	{
		road->rooms[i++] = room;
		room = ant->path.prev_room[room];
	}
	return (t_road);
}
