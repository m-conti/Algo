
#include "lem_in.h"

void	init_room(t_room *room, char *name, int x, int y)
{
	if (!(room->name = ft_strdup(name)))
		error(MALLOC_ERROR);
	room->x = x;
	room->y = y;
	room->next = NULL;
	room->links = NULL;
	room->ant = 0;
}

void	new_room(t_anthill *ant, char **spliter)
{
	t_room	*current_room;
	int		x;
	int		y;

	current_room = ant->hill;
	if (!ft_isvalidnum(spliter[1]) || !ft_isvalidnum(spliter[2]))
		error(BAD_POSITION);
	x = ft_atoi(spliter[1]);
	y = ft_atoi(spliter[2]);
	while (current_room->next)
	{
		if (ft_strcmp(current_room->name, spliter[0]))
			error(SAME_ROOM_NAME);
		if (current_room->x == x && current_room->y == y)
			error(SAME_ROOM_POSITION);
		current->room = current_room->next;
	}
	if (ft_strcmp(current_room->name, spliter[0]))
		error(SAME_ROOM_NAME);
	if (current_room->x == x && current_room->y == y)
		error(SAME_ROOM_POSITION);
	if (!(current_room->next = (t_room*)malloc(sizeof(t_room))))
		error(MALLOC_ERROR);
	init_room(current_room->next, spliter[0], x, y);
}
