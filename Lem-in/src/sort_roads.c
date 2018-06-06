/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_roads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:02:14 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 17:24:07 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	switch_road(t_road *road, t_road *to_copy)
{
	road->rooms = to_copy->rooms;
	road->len = to_copy->len;
	to_copy->len = 0;
}

int		road_to_tab(t_road *road_check, t_road **to_copy, int n)
{
	while (road_check)
	{
		if ((n = road_check->len))
			*to_copy = road_check;
		if (n)
			break ;
		road_check = road_check->next;
	}
	while (road_check && (road_check = road_check->next))
		if (road_check->len && road_check->len < n && (n = road_check->len))
			*to_copy = road_check;
	return (n);
}

void	free_road(t_road *road)
{
	t_road	*tmp;

	while (road)
	{
		tmp = road->next;
		free(road);
		road = tmp;
	}
}

void	sorting_roads(t_anthill *ant)
{
	t_road	*racine;
	t_road	*road_check;
	t_road	*to_copy;
	int		n;
	int		i;

	racine = ant->road;
	to_copy = NULL;
	i = 0;
	n = 1;
	if (!(ant->road = (t_road*)ft_memalloc(sizeof(t_road) * ant->n_roads)))
		error(MALLOC_ERROR);
	while (n)
	{
		road_check = racine;
		n = road_to_tab(road_check, &to_copy, n);
		if (n)
			switch_road(&ant->road[i++], to_copy);
	}
	free_road(racine);
}
