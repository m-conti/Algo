/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:53:57 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 18:49:18 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_anthill(t_anthill *ant)
{
	ant->stop = 0;
	ant->hill = NULL;
	if (!(ant->hill = (t_room*)ft_memalloc(sizeof(t_room))))
		error(MALLOC_ERROR);
	ant->hill->name = NULL;
	ant->nb_ant = 0;
	ant->nb_room = 0;
	ant->start = -1;
	ant->end = -1;
	ant->lines = NULL;
	ant->parstatus = NB_ANT_CHECK;
	ant->check_status[NB_ANT_CHECK] = &check_status_nb_ant;
	ant->check_status[ROOM_CHECK] = &check_status_room;
	ant->check_status[TUBE_CHECK] = &check_status_tube;
}

void	init_room(t_room *room, char *name, int x, int y)
{
	if (!(room->name = ft_strdup(name)))
		error(MALLOC_ERROR);
	room->x = x;
	room->y = y;
	room->next = NULL;
	room->route_number = 0;
}
