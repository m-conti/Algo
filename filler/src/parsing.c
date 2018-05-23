/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:36:00 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/22 15:34:04 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
 ** init_free_tab mallocs f->tab if it doesn't exist,
 ** and free every line for further use
 */

int		error(t_filler *f, int err_type)
{
	f->error = err_type;	
	return (err_type);
}

int    init_free_tab(t_filler *f)
{
	int i;

	if (!(f->tab))
	{
		if(!(f->tab = (char**)malloc(sizeof(char*) * f->ymax)))
			return (error(f, ERROR_MALLOC));
	}
	else
	{
		i = 0;
		while (i < f->ymax)
		{
			ft_strdel(&f->tab[i]);
			i++;
		}
	}
	return (0);
}

int	build_piece(t_filler *f)
{
	int		r;
	char	*pos;
	char	*line;

	if (get_next_line(0, &line) != 1)
		return (error(f, ERROR_BAD_INPUT));
	if (ft_strncmp(line, "Piece ", 6) != 0)
		return (error(f, ERROR_BAD_INPUT));
	pos = ft_strchr(line, ' ') + 1;
	if (!(ft_isdigit(*pos)))
		return (error(f, ERROR_BAD_INPUT));
	f->piece.ymax = ft_atoi(pos);
	pos = ft_strchr(pos, ' ') + 1;
	if (!(ft_isdigit(*pos)))
		return (error(f, ERROR_BAD_INPUT));
	f->piece.xmax = ft_atoi(pos);
	if (!(f->piece.tab = (char**)malloc(sizeof(char*) * f->piece.ymax)))
		return (error(f, ERROR_MALLOC));
	ft_strdel(&line);
	r = -1;
	while (++r < f->piece.ymax)
	{
		if (!(f->piece.tab[r] = (char*)malloc(sizeof(char) * f->piece.xmax)))
			return (error(f, ERROR_MALLOC));
		if (get_next_line(0, &(f->piece.tab[r])) != 1)
			return (error(f, ERROR_BAD_INPUT));
		if (!((int)ft_strlen(f->piece.tab[r]) == f->piece.xmax))
			return (error(f, ERROR_BAD_INPUT));
	}
	return (0);
}		

void	ft_free_strarray(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_strdel(&arr[i]);
		i++;
	}
	ft_memdel((void**)arr);
}

int		parse_tab(t_filler *f)
{
	int		row;
	char	**split_line;
	char	*line;

	if (!f->player)
		parse_first_time(f);
	if (f->error)
		return (f->error);
	init_free_tab(f);
	get_next_line(0, &line);
	ft_strdel(&line);
	row = RESET_COUNT;
	while (++row < f->ymax)
	{
		if (get_next_line(0, &line) != 1)
			return (error(f, ERROR_BAD_INPUT));
		if (!(split_line = ft_strsplit(line, ' ')))
			return (error(f, ERROR_BAD_INPUT));
		ft_strdel(&line);
		if (ft_atoi(split_line[0]) != row)
			return (error(f, ERROR_BAD_INPUT));
		if ((int)ft_strlen(split_line[1]) != f->xmax)
			return (error(f, ERROR_BAD_INPUT));
		f->tab[row] = split_line[1];
	}
	if (f->display)
		parse_tab_display(f);
	if (!f->frontier)
		set_frontier(f);
	return (0);
}

int		parse_first_time(t_filler *f)
{
	char **plateau_line;
	char *line;

	if ((get_next_line(0, &line) != 1))
		return (error(f, ERROR_BAD_INPUT));
	if (ft_strncmp("$$$ exec p1", line, 11) == 0)
		f->player = 'O';
	else if (ft_strncmp("$$$ exec p2", line, 11) == 0)
		f->player = 'X';
	else
		return (error(f, ERROR_BAD_INPUT));
	ft_strdel(&line);
	if ((get_next_line(0, &line) != 1))
		return (error(f, ERROR_BAD_INPUT));
	if (ft_strncmp("Plateau ", line, 8) == 0)
	{
		if (!(plateau_line = ft_strsplit(line, ' ')))
			return (error(f, ERROR_BAD_INPUT));
		ft_strdel(&line);
		if (!(plateau_line[1] && plateau_line[2]))
			return (error(f, ERROR_BAD_INPUT));
		if (!(ft_isdigit(plateau_line[1][0])))
			return (error(f, ERROR_BAD_INPUT));
		f->ymax = ft_atoi(plateau_line[1]);
		if (!(ft_isdigit(plateau_line[2][0])))
			return (error(f, ERROR_BAD_INPUT));
		f->xmax = ft_atoi(plateau_line[2]);
		if (f->ymax < 1 || f->xmax < 1 || !(f->ymax >= 2 || f->xmax >= 2))
			return (error(f, ERROR_BAD_INPUT));
		ft_free_strarray(plateau_line);
	}
	else
		return (error(f, ERROR_BAD_INPUT));
	if (f->display)
		parse_first_time_display(f);
	return (0);
}
