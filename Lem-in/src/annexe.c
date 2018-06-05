/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:03:59 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/05 18:41:15 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_isvalidnum(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (0);
		i++;
	}
	return (1);
}

int		ft_tablen(char **split)
{
	int len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}

void	reorganize_hill(t_anthill *ant)
{
	t_room	*room;
	t_room	*tmp;
	int		i;

	if (ant->start == ant->nb_room || ant->end == ant->nb_room ||
			ant->start == -1 || ant->end == -1)
		error(NO_ESCAPE);
	if (ant->end == ant->start)
		error(FREEDOM);
	room = ant->hill;
	i = 0;
	if (!(ant->hill = (t_room*)ft_memalloc(sizeof(t_room) * ant->nb_room)))
		error(MALLOC_ERROR);
	while (i < ant->nb_room)
	{
		tmp = room->next;
		room_copy(ant, room, i++);
		room = tmp;
	}
}

void	increase_links(t_anthill *ant, int room)
{
	int		*tmp;
	int		i;

	tmp = ant->hill[room].links;
	if (!(ant->hill[room].links = (int*)ft_memalloc(sizeof(int)
					* (ant->hill[room].nb_links + SIZE_LINKS))))
		error(MALLOC_ERROR);
	i = RESET_COUNT;
	while (++i < ant->hill[room].nb_links)
		ant->hill[room].links[i] = tmp[i];
	if (tmp)
		free(tmp);
}

void	add_links(t_anthill *ant, int room1, int room2)
{
	int		i;
	uint8_t	already_linked;

	i = RESET_COUNT;
	already_linked = 0;
	if (!(ant->hill[room1].nb_links % SIZE_LINKS))
		increase_links(ant, room1);
	if (!(ant->hill[room2].nb_links % SIZE_LINKS))
		increase_links(ant, room2);
	while (!already_linked && ++i < ant->hill[room1].nb_links)
		if (ant->hill[room1].links[i] == room2)
			already_linked = 1;
	if (!already_linked)
	{
		ant->hill[room1].links[ant->hill[room1].nb_links] = room2;
		ant->hill[room1].nb_links++;
		ant->hill[room2].links[ant->hill[room2].nb_links] = room1;
		ant->hill[room2].nb_links++;
	}
}
