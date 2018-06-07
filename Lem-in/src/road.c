/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:58:58 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 18:42:35 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	calc_nmax_road(t_anthill *ant)
{
	int max;

	max = ant->nb_ant;
	if (ant->hill[ant->start].nb_links < max)
		max = ant->hill[ant->start].nb_links;
	if (ant->hill[ant->end].nb_links < max)
		max = ant->hill[ant->end].nb_links;
	ant->nmax_road = max;
	if (max < 1)
		error(NO_ESCAPE);
}

t_road	*new_road(t_anthill *ant, int len_road)
{
	t_road *new_road;

	if (!(new_road = (t_road*)ft_memalloc(sizeof(t_road))))
		error(MALLOC_ERROR);
	if (!(new_road->rooms = ft_memalloc(sizeof(int) * len_road)))
		error(MALLOC_ERROR);
	new_road->rooms[0] = ant->start;
	new_road->len = len_road;
	return (new_road);
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
			r->rooms[i] = ant->path[r->rooms[i + 1]];
	}
	free(ant->path);
	return (r);
}

void	build_fastest_roads(t_anthill *ant)
{
	int		i;
	t_road	*road;
	int		tmp;

	road = NULL;
	tmp = 0;
	if (ant->nmax_road == 1 && ++tmp)
		ant->road = build_road(ant, new_road(ant, dijkstra(ant, 0)));
	else if ((i = RESET_COUNT))
		while (++i < ant->n_roads)
			if (ant->finished_roads[i])
			{
				tmp++;
				if (!road)
				{
					ant->road = build_road(ant, new_road(ant,
								dijkstra(ant, i + 1)));
					road = ant->road;
				}
				else if ((road->next =
					build_road(ant, new_road(ant, dijkstra(ant, i + 1)))))
					road = road->next;
			}
	ant->n_roads = tmp;
}
