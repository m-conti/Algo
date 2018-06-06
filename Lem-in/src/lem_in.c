/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:41:27 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 19:47:59 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_line_to_print(t_anthill *ant)
{
	if (!(ant->lines = ft_strjoinfree(ant->lines, ant->current_line, 1)))
		error(MALLOC_ERROR);
	if (!(ant->lines = ft_strjoinfree(ant->lines, "\n", 1)))
		error(MALLOC_ERROR);
}

void	parse(t_anthill *ant)
{
	int		ret;

	while (!ant->stop && (ret = get_next_line(0, &(ant->current_line))))
	{
		if (ret == -1)
			error(GNL_ERROR);
		if (!(ant->current_line[0]))
			error(EMPTY_LINE);
		if (ant->current_line[0] != '#')
			ant->check_status[ant->parstatus](ant);
		else if (ant->current_line[1] == '#')
			check_command(ant);
		if (!ant->stop)
			add_line_to_print(ant);
		ft_strdel(&ant->current_line);
	}
}

void	error(int err_nb)
{
	if (DEBUG)
		ft_printf("Error n %d\n", err_nb);
	ft_printf("ERROR\n");
	exit(1);
}

void	free_all(t_anthill *ant)
{
	int		i;

	ft_strdel(&ant->lines);
	ft_memdel((void**)&ant->finished_roads);
	i = RESET_COUNT;
	while (++i < ant->n_roads)
	{
		ft_memdel((void**)&ant->road[i].rooms);
		ft_memdel((void**)&ant->road[i]);
	}
	ft_memdel((void**)&ant->road);
	i = RESET_COUNT;
	while (++i < ant->nb_room)
	{
		ft_strdel(&ant->hill[i].name);
		ft_memdel((void**)&ant->hill[i].links);
		ft_memdel((void**)&ant->hill[i]);
	}
	ft_memdel((void**)&ant->hill);
}

int		main(void)
{
	t_anthill	ant;

	init_anthill(&ant);
	parse(&ant);
	calc_nmax_road(&ant);
	assign_rooms_to_routes(&ant);
	build_fastest_roads(&ant);
	sorting_roads(&ant);
	ft_putendl(ant.lines);
	print_solution(&ant);
	free_all(&ant);
	return (0);
}
