/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:29:03 by mconti            #+#    #+#             */
/*   Updated: 2018/06/02 03:29:05 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.c"

typedef struct 			s_queue;
{
	int					room;
	t_road				*road;
	struct s_queue		*next;
}						t_queue;

typedef	struct			s_road
{
	int					*rooms;
	int					len;
	struct s_road		*next;
}						t_road;

t_road		*new_road(t_anthill *ant)
{
	t_road *new_road;

	if (!(new_road = (t_road*)malloc(sizeof(t_road))))
		error(MALLOC_ERROR);
	new_road->next = NULL;
	if (!(new_road->rooms = ft_memalloc(sizeof(int) * SIZE_ROAD)))
		error(MALLOC_ERROR);
	new_road->rooms[0] = ant->start;
	new_road->len = 0;
}

t_queue		*add_queue(int room, t_road *road)
{
	t_queue	*new_queue;

	if (!(new_queue = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	new_queue->room = room;
	new_queue->road = road;
	return (new_queue);
}

t_queue		*next_queue(t_queue *queue)
{
	t_queue	*tmp;

	tmp = queue->next;
	free(queue);
	return (tmp);
}

t_queue		*trace_roads(t_anthill *ant, t_queue *queue, t_road *all_roads)
{
	int		i;

	i = RESET_COUNT;
	if (queue->room == ant->end)
	{
		valid_road(all_roads, queue);
		return (next_queue(queue));
	}
	while (++i < ant->hill[queue->room].nb_links)
	{
		if (ant->hill[queue->room].links[i] != start && (!ant->hill[queue->room].links[i] || ant->path[ant->hill[queue->room].links[i]] < ant->path[ant->hill[queue->room]]))
	}
}

t_road		*make_road(t_anthill *ant)
{
	t_queue	*queue;
	t_road	*all_roads;
	int		n;

	if (!(ant->path.distance = (int*)ft_memalloc(sizeof(int) * ant->nb_room)))
		error(MALLOC_ERROR);
	queue = add_queue(ant->start, new_road(ant));
	all_roads = NULL;
	n = 0;
	while (n < ant->nmax_road && queue)
	{
		queue = trace_roads(ant, queue, all_roads);
		n = check_numbers_roads(ant, all_roads);
	}
}
