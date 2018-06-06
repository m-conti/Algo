/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:34:15 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 19:48:01 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	dijkstra_core(t_anthill *ant, t_queue **q, int *visited, int road_to_build)
{
	int i;
	int len_road;

	len_road = ant->hill[(*q)->room].len_from_start;
	i = RESET_COUNT;
	while (++i < ant->hill[(*q)->room].nb_links)
	{
		if (ant->hill[(*q)->room].links[i] == ant->end)
		{
			ant->path.prev_room[ant->end] = (*q)->room;
			free_all_queue(q);
			break ;
		}
		if ((ant->hill[ant->hill[(*q)->room].links[i]].route_number
				== road_to_build)
				&& (!visited[ant->hill[(*q)->room].links[i]]))
		{
			ant->hill[ant->hill[(*q)->room].links[i]].len_from_start =
				len_road + 1;
			add_to_queue(*q, ant->hill[(*q)->room].links[i]);
			visited[ant->hill[(*q)->room].links[i]] = 1;
			ant->path.prev_room[ant->hill[(*q)->room].links[i]] = (*q)->room;
		}
	}
	return (len_road);
}

int	dijkstra(t_anthill *ant, int road_to_build)
{
	t_queue	*q;
	int		*visited;
	int		len_road;

	if (!(visited = (int*)ft_memalloc(sizeof(int) * ant->nb_room)) ||
		!(ant->path.prev_room = (int*)ft_memalloc(sizeof(int) * ant->nb_room)))
		error(MALLOC_ERROR);
	q = create_queue(ant->start);
	while (q && q->room != ant->end)
	{
		len_road = dijkstra_core(ant, &q, visited, road_to_build);
		if (q)
			q = next_element(q);
	}
	ft_memdel((void**)&visited);
	return (len_road + 1);
}
