/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:28:51 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 17:55:20 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_duplicate_rooms(char *name, t_room **current_room, t_point p)
{
	while (1)
	{
		if (!ft_strcmp((*current_room)->name, name))
			error(SAME_ROOM_NAME);
		if ((*current_room)->x == p.x && (*current_room)->y == p.y)
			error(SAME_ROOM_POSITION);
		if (!(*current_room)->next)
			break ;
		(*current_room) = (*current_room)->next;
	}
}

void	new_room(t_anthill *ant, char **sp)
{
	t_room	*current_room;
	t_point p;
	int		len;
	char	*name;

	current_room = ant->hill;
	len = ft_tablen(sp);
	if (len < 3 || !ft_isvalidnum(sp[len - 1]) || !ft_isvalidnum(sp[len - 2]))
		error(INVALID_ROOM);
	p.x = ft_atoi(sp[len - 2]);
	p.y = ft_atoi(sp[len - 1]);
	name = get_room_name(ant->current_line);
	if (!current_room->name)
		init_room(current_room, name, p.x, p.y);
	else
	{
		check_duplicate_rooms(name, &current_room, p);
		if (!(current_room->next = (t_room*)ft_memalloc(sizeof(t_room))))
			error(MALLOC_ERROR);
		init_room(current_room->next, name, p.x, p.y);
	}
}

char	*get_room_name(char *src)
{
	int	i;
	int	space_invader;

	space_invader = 0;
	if (!src && !src[0])
		return (NULL);
	i = ft_strlen(src) - 1;
	while (src[i] == ' ')
		i--;
	while (space_invader < 2 && i > 0)
		if (i > 0 && src[i--] == ' ')
			space_invader++;
	return (ft_strsub(src, 0, i + 1));
}

void	room_copy(t_anthill *ant, t_room *room, int n)
{
	ant->hill[n].name = room->name;
	ant->hill[n].x = room->x;
	ant->hill[n].y = room->y;
	free(room);
}

int		is_room_name(t_anthill *ant, char *name, int *room)
{
	int i;

	i = 0;
	while (i < ant->nb_room)
	{
		if (!(ft_strcmp(ant->hill[i].name, name)))
		{
			*room = i;
			return (1);
		}
		i++;
	}
	return (0);
}
