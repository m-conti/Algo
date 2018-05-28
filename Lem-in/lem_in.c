#include "lem_in.h"

void	init_anthill(t_anthill *ant)
{
	ant->hill = NULL;
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

void	check_line(t_anthill *ant)
{
	if (!ant->currentline[0])
		error(EMPTY_LINE);
	if (ant->current_line[0] != '#')
		ant->check_status[ant->parstatus](ant);
	else if (ant->current_line[1] == '#')
		check_command(ant);
	add_string(ant);
}

void	parse(t_anthill *ant)
{
	int		ret;

	while ((ret = get_next_line(0, &ant->current_line)))
	{
		if (ret != 1)
			error(GNL_ERROR);
		check_line(ant);
	}
}

int		main(void)
{
	t_anthill	ant;

	init_anthill(&ant);
	parse(&ant);
	return (0);
}