#include "lem_in.h"

void	show_rooms(t_anthill* ant)
{	
	int i;
	int j;

	i = RESET_COUNT;
	while (++i < ant->nb_room)
	{
		if (i == ant->start)
			ft_printf("(Start)\n");
		if (i == ant->end)
			ft_printf("(End)\n");
		ft_printf("Room %i, name=%s, nb_links=%i\n", i, ant->hill[i].name, ant->hill[i].nb_links);
		if (ant->hill[i].nb_links >= 1)
		{
			j = RESET_COUNT;
			while (++j < ant->hill[i].nb_links)
				ft_printf("%10d\n", ant->hill[i].links[j]);
		}
		if (ant->hill[i].route_number)
			ft_printf("\tRoute Number = %d\n", ant->hill[i].route_number);

	}
}

void	show_roads(t_anthill* ant)
{
	t_road	*cur;
	int		i;
	int		j;

	cur = ant->road;
	i = 1;
	while (cur)
	{
		ft_printf("Road %i\n", i);
		j = RESET_COUNT;
		while (++j < cur->len)
		{
			if (j == 0)
				ft_printf("%s (%i)", ant->hill[cur->rooms[j]].name, cur->rooms[j]);
			else
				ft_printf("->%s (%i)", ant->hill[cur->rooms[j]].name, cur->rooms[j]);
		}
		ft_printf("\n\n");
		i++;
		cur = cur->next;
	}
}
