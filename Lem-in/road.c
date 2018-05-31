#include "lem_in.c"

void	calc_nmax_road(t_anthill *ant)
{
	int	max;

	max = ant->nb_ant;
	if (ant->hill[ant->start].nb_links < max)
		max = ant->hill[ant->start].nb_links;
	if (ant->hill[ant->end].nb_links < max)
		max = ant->hill[ant->end].nb_links;
	ant->nmax_road = max;
	if (max < 1)
		error(NO_ESCAPE)
}

void	find_road(t_anthill *ant, t_room *current_room, t_road *current_road)
{

}