
#include "lem_in.h"

void	init_room(t_room *room, char *name, int x, int y)
{
	if (!(room->name = ft_strdup(name)))
		error(MALLOC_ERROR);
	room->x = x;
	room->y = y;
	room->next = NULL;
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
	while (1)
	{
		if (ft_strcmp(current_room->name, name))
			error(SAME_ROOM_NAME);
		if (current_room->x == p.x && current_room->y == p.y)
			error(SAME_ROOM_POSITION);
		if (!current_room->next)
			break ;
		current_room = current_room->next;
	}
	if (!(current_room->next = (t_room*)malloc(sizeof(t_room))))
		error(MALLOC_ERROR);
	init_room(current_room->next, name, p.x, p.y);
}
