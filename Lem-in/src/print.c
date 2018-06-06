/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 19:14:31 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 17:43:18 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_ants_to_open(t_anthill *ant)
{
	int	i;

	i = 0;
	while (++i < ant->n_roads)
	{
		ant->road[i].nb_ants_to_open =
			ant->road[i - 1].nb_ants_to_open +
			(i * (ant->road[i].len - ant->road[i - 1].len)) + 1;
	}
}

void	print_new_leaving(t_anthill *ant, int *n_ant, t_road *road)
{
	ant->hill[road->rooms[0]].ant = ++*n_ant;
	if (!ant->stop)
		ft_printf("L%i-%s", ant->hill[road->rooms[0]].ant,
				ant->hill[road->rooms[0]].name);
	else
		ft_printf(" L%i-%s", ant->hill[road->rooms[0]].ant,
				ant->hill[road->rooms[0]].name);
	ant->stop = 1;
}

int		forward_in_road(t_anthill *ant, int *n_ant, t_road *road)
{
	int		i;

	i = road->len - 1;
	while (--i >= 0)
	{
		if (ant->hill[road->rooms[i]].ant)
		{
			ant->hill[road->rooms[i + 1]].ant = ant->hill[road->rooms[i]].ant;
			if (!ant->stop)
				ft_printf("L%i-%s", ant->hill[road->rooms[i]].ant,
						ant->hill[road->rooms[i + 1]].name);
			else
				ft_printf(" L%i-%s", ant->hill[road->rooms[i]].ant,
						ant->hill[road->rooms[i + 1]].name);
			ant->hill[road->rooms[i]].ant = 0;
			ant->stop = 1;
		}
	}
	if (ant->nb_ant - *n_ant > road->nb_ants_to_open)
		print_new_leaving(ant, n_ant, road);
	if (ant->hill[road->rooms[road->len - 1]].ant == ant->nb_ant)
		return (0);
	return (1);
}

void	print_solution(t_anthill *ant)
{
	int		n_ant;
	int		i;
	uint8_t	last;

	n_ant = 0;
	last = 1;
	if (ant->road[0].len == 1)
	{
		i = 1;
		ft_printf("L%i-%s", i, ant->hill[ant->end]);
		while (++i < ant->nb_ant)
			ft_printf(" L%i-%s", i, ant->hill[ant->end]);
		ft_putchar('\n');
		return ;
	}
	set_ants_to_open(ant);
	while (last)
	{
		ant->stop = 0;
		i = ant->n_roads;
		while (--i >= 0)
			last = forward_in_road(ant, &n_ant, &ant->road[i]);
		ft_printf("\n");
	}
}
