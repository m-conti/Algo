/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:44:51 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 19:37:47 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (ft_index(ant->current_line, '-') >= 0)
	{
		ant->parstatus = TUBE_CHECK;
		reorganize_hill(ant);
		check_status_tube(ant);
		return ;
	}
	if (ant->current_line[0] == 'L')
		error(HELL_ROOM);
	spliter = ft_strsplit(ant->current_line, ' ');
	new_room(ant, spliter);
	ant->nb_room++;
	ft_tabdel((void**)spliter, -1);
}

void	check_status_tube(t_anthill *ant)
{
	char		**spliter;
	int			room1;
	int			room2;

	spliter = ft_strsplit(ant->current_line, '-');
	if (!(spliter[0] && spliter[1] && !spliter[2]) ||
		(!is_room_name(ant, spliter[0], &room1)) ||
		(!is_room_name(ant, spliter[1], &room2)))
	{
		ft_tabdel((void**)spliter, -1);
		ant->stop = 1;
		return ;
	}
	if (ft_strcmp(spliter[0], spliter[1]))
		add_links(ant, room1, room2);
	ft_tabdel((void**)spliter, -1);
}

void	check_command(t_anthill *ant)
{
	if (!ft_strcmp(&ant->current_line[2], "start"))
	{
		if (ant->start == -1)
			ant->start = ant->nb_room;
	}
	else if (!ft_strcmp(&ant->current_line[2], "end"))
	{
		if (ant->end == -1)
			ant->end = ant->nb_room;
	}
}
