
#include "lem_in.h"

void	check_status_nb_ant(t_anthill *ant)
{
	int		i;
	char	*over_check;

	i = 0;
	while (ant->current_line[i])
		if (!ft_isdigit(ant->current_line[i++]))
			error(WRONG_ANT_NUMBER);
	ant->nb_ant = ft_atoi(ant->current_line);
	over_check = ft_itoa(ant->nb_ant);
	i = 0;
	while (ant->current_line[i] == '0')
		i++;
	if (ft_strcmp(&ant->current_line[i], over_check))
		error(WRONG_ANT_NUMBER);
	ft_strdel(&over_check);
	ant->parstatus = ROOM_CHECK;
}

void	check_status_room(t_anthill *ant)
{
	char	**spliter;

	spliter = ft_strsplit(ant->current_line, ' ');
	if (spliter[1] && spliter[2] && !spliter[3])
	{
		if (spliter[0][0] == 'L')
			error(HELL_ROOM);
		new_room(ant, spliter);
	}
	else
	{
		ant->parstatus = TUBE_CHECK;
		check_status_tube(ant);
	}
	ft_tabdel((void**)spliter, -1);
}

void	check_status_tube(t_anthill *ant)
{
	char **spliter;

	spliter = ft_strsplit(ant->current_line, '-');
	if (!spliter[0] || !spliter[1] || spliter[2])
		error(FATAL_ERROR);
	
}

void	check_command(t_anthill *ant)
{
	if (!ft_strcmp(ant->current_line[2], "start"))
	{
		if (ant->start != -1)
			error(MULTIPLE_START);
		else
			ant->start = ant->nb_room;
	}
	else if (!ft_strcmp(ant->current_line[2], "end"))
	{
		if (ant->end != -1)
			error(MULTIPLE_END);
		else
			ant->end = ant->nb_room;
	}
	//check qu'il y a une room après start || end;
}
