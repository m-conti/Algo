
#include "lem_in.h"

void	init_room(t_room *room, char *name, int x, int y)
{
	if (!(room->name = ft_strdup(name)))
		error(MALLOC_ERROR);
	room->x = x;
	room->y = y;
	room->next = NULL;
	room->route_number = 0;
}

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
		while (1)
		{
			if (!ft_strcmp(current_room->name, name))
				error(SAME_ROOM_NAME);
			if (current_room->x == p.x && current_room->y == p.y)
				error(SAME_ROOM_POSITION);
			if (!current_room->next)
				break ;
			current_room = current_room->next;
		}
		if (!(current_room->next = (t_room*)ft_memalloc(sizeof(t_room))))
			error(MALLOC_ERROR);
		init_room(current_room->next, name, p.x, p.y);
	}
}
