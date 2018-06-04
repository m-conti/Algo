#include "lem_in.h"

char	*get_room_name(char	*src)
{
	int		i;
	int		space_invader;

	space_invader = 0;
	if (!src && !src[0])
		return (NULL);
	i = ft_strlen(src) - 1;
	while (src[i] == ' ')
		i--;
	while(space_invader < 2 && i > 0)
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

void	increase_links(t_anthill *ant, int room)
{
	int		*tmp;
	int		i;

	tmp = ant->hill[room].links;
	if (!(ant->hill[room].links = (int*)malloc
		(sizeof(int) * ant->hill[room].nb_links + SIZE_LINKS)))
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

void	error(int err_nb)
{
	ft_printf("Error n %d\n", err_nb);
	exit(1);
}
