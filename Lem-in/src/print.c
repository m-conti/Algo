
#include "lem_in.h"

void	switch_road(t_road *road, t_road *to_copy)
{
	road->rooms = to_copy->rooms;
	road->len = to_copy->len;
	to_copy->len = 0;
}

void	sorting_roads(t_anthill *ant)
{
	t_road	*racine;
	t_road	*road_check;
	t_road	*to_copy;
	int		n;
	int		i;

	racine = ant->road;
	i = 0;
	n = 1;
	if (!(ant->road = (t_road*)ft_memalloc(sizeof(t_road) * ant->n_roads)))
		error(MALLOC_ERROR);
	while (n)
	{
		road_check = racine;
		while (road_check)
		{
			if ((n = road_check->len))
				to_copy = road_check;
			if (n)
				break ;
			road_check = road_check->next;
		}
		while (road_check && (road_check = road_check->next))
			if (road_check->len && road_check->len < n && (n = road_check->len))
				to_copy = road_check;
		if (n)
			switch_road(&ant->road[i++], to_copy);
	}
	road_check = racine;
	while (road_check)
	{
		to_copy = road_check->next;
		free(road_check);
		road_check = to_copy;
	}
}

void	set_ants_to_open(t_anthill *ant)
{
	int		i;

	i = 0;
	while (++i < ant->n_roads)
	{
		ant->road[i].nb_ants_to_open =
		ant->road[i - 1].nb_ants_to_open +
		(i * (ant->road[i].len - ant->road[i - 1].len)) + 1;
		ft_printf("for road %2i set open at: %2i ants\n", i + 1, ant->road[i].nb_ants_to_open);
	}
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
			ft_printf("L%i-%s ", ant->hill[road->rooms[i]].ant, ant->hill[road->rooms[i + 1]].name);
			ant->hill[road->rooms[i]].ant = 0;
		}
	}
//	ft_printf("nb_ant: %i - no_ant: %i >= road->nb_ants_to_open: %i", ant->nb_ant, *n_ant, road->nb_ants_to_open);
	if (ant->nb_ant - *n_ant > road->nb_ants_to_open)
	{
		ant->hill[road->rooms[0]].ant = ++*n_ant;
		ft_printf("L%i-%s ", ant->hill[road->rooms[0]].ant, ant->hill[road->rooms[0]].name);
	}
	if (ant->hill[road->rooms[road->len - 1]].ant == ant->nb_ant)
		return (0);
	return (1);
}

void	print_solution(t_anthill *ant)
{
	int			n_ant;
	int 		i;
	uint8_t		last;

	n_ant = 0;
	last = 1;
	if (ant->road[0].len == 1)
	{
		ft_printf("toutes d'un coup bim\n");
		return ;
	}
	set_ants_to_open(ant);
	while (last)
	{
		i = ant->n_roads;
		while (--i >= 0)
			last = forward_in_road(ant, &n_ant, &ant->road[i]);
		ft_printf("\n");
	}
}
