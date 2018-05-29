
#include "lem_in.h"

void	new_room(t_anthill *ant, char **spliter)
{
	t_room	*current_room;
	t_room	*new_room;

	current_room = ant->hill;
	while (current_room)
	{
		if (ft_strcmp(current_room->name, spliter[0]))
			error(SAME_ROOM_NAME);
		current->room = current_room->next;
	}
}
