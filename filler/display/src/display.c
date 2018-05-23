/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:05:56 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/23 17:37:52 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int		usage(void)
{
	ft_putstr("Usage: ./display filler.trace\n");
	return (1);
}

void	print_square(int size, int color, t_point *p, t_display_mlx *d)
{
	int x;
	int y;

	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
			mlx_pixel_put(d->mlx, d->win, p->x + x, p->y + y, color);
	}
}

int	deal_key(int key, void *param)
{
	t_display_mlx	*d;
	t_point			p;

	if (key == ESC_KEY)
		exit(0);

	d = (t_display_mlx*)param;
	//mlx_pixel_put(d->mlx, d->win, key, key, 255);	
	p.x = key;
	p.y = key;
	print_square(d->sq_size, GREEN, &p, d); 
	ft_printf("key: %d\n", key);
	return (0);
}

void	init_display(t_display_mlx *d)
{
	t_point	p;

	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	d->sq_size = SQ_SIZE;
	p.y = 100;
	p.x = 20;
	print_square(WIN_WIDTH - 2 * p.x, DARK_GRAY, &p, d); 
	mlx_string_put(d->mlx, d->win,
			X_PLAYER_NAME, Y_PLAYER_NAME, PLAYER_COLOR, "tbehra.filler"); 
	mlx_string_put(d->mlx, d->win,
			X_PLAYER_NAME, Y_PLAYER_NAME + 20, TEXT_COLOR, "Score:"); 
	mlx_string_put(d->mlx, d->win,
			X_PLAYER_NAME, Y_PLAYER_NAME + 40, TEXT_COLOR, "Territory:"); 
	mlx_string_put(d->mlx, d->win,
			X_CHALLENGER_NAME, Y_PLAYER_NAME, CHALLENGER_COLOR, "Challenger"); 
	mlx_string_put(d->mlx, d->win,
			X_CHALLENGER_NAME, Y_PLAYER_NAME + 20, TEXT_COLOR, "Score:"); 
	mlx_string_put(d->mlx, d->win,
			X_CHALLENGER_NAME, Y_PLAYER_NAME + 40, TEXT_COLOR, "Territory:"); 
	mlx_string_put(d->mlx, d->win, Y_TURN, X_TURN, TEXT_COLOR, "Turn 1");
}


char	**parse_tab(t_display_mlx *d)
{
	char	*line;
	char	**ret;
	int		r;
	int		c;

	r = -1;
	if (!(ret = (char**)malloc(sizeof(char*) * d->ymax + 1)))
		return (0);
	while (++r < d->ymax)
	{
		if (get_next_line(d->fd, &line) != 1)
			return (0);
		if ((int)ft_strlen(line) != d->xmax)
			return (0);
		if (!(ret[r] = (char*)malloc(sizeof(char) * d->xmax + 1)))
			return (0);
		c = -1;
		ft_strcpy(ret[r], line);
		ft_strdel(&line);
	}
	return (ret);
}

void    free_tab_content(void **tab, int max)
{
	int i;

	if (tab)
	{
		i = 0;
		while (i < max)
		{
			free(tab[i]);
			i++;
		}
	}
}

int	parse_tab_frontier(t_display_mlx *d)
{
	char	*line;
	//FREE
	if (d->tab)
	{
		free_tab_content((void**)d->tab, d->ymax);
		free(d->tab);
		free_tab_content((void**)d->frontier, d->ymax);
		free(d->frontier);
	}
	ft_putstr("TEST\n\n");
	if (!(d->tab = parse_tab(d)))
		return (0);
	if (get_next_line(d->fd, &line) != 1)
		return (0);
	ft_strdel(&line);
	if (!(d->tab = parse_tab(d)))
		return (0);
	if (get_next_line(d->fd, &line) != 1)
		return (0);
	ft_strdel(&line);
	return (1);
}

int	parse_map_params(t_display_mlx *d)
{
	char *line;

	if (get_next_line(d->fd, &line) != 1)
		return (0);
	d->player = (line[0] == 'O') ? 1 : 2;
	ft_strdel(&line);
	if (get_next_line(d->fd, &line) != 1)
		return (0);
	if (!(ft_isdigit(line[0])))
		return (0);
	d->ymax = ft_atoi(line);
	ft_strdel(&line);
	if (get_next_line(d->fd, &line) != 1)
		return (0);
	d->xmax = ft_atoi(line);
	ft_strdel(&line);
	return (1);
}

int	main(int ac, char **av)
{
	t_display_mlx	d;

	if (ac < 2)
	{
		if (!(d.fd = open("filler.disp", O_RDONLY)))
			return (usage());
	}
	else if (!(d.fd = open(av[1], O_RDONLY)))
		return (usage());
	ft_putstr("TEST1");
	if (!(parse_map_params(&d)))
		return (1);
	if (!(parse_tab_frontier(&d)))
		return (1);
	init_display(&d);
	mlx_key_hook(d.win, &deal_key, &d); 
	mlx_loop(d.mlx);
	return (0);
}
