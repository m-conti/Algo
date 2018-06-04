
#include "lem_in.h"

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

t_queue		*next_element(t_queue *q)
{
	t_queue	*tmp;

	tmp = q->next;
	free(q);
	return (tmp);
}

t_queue		*create_queue(int content)
{
	t_queue	*queue;

	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		error(MALLOC_ERROR);
	queue->room = content;
	queue->next = NULL;
	return (queue);
}

t_queue		*path_room(t_anthill *ant, t_queue *rooms_to_check)
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
