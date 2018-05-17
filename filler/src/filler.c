/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:35:36 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/17 15:11:08 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"


#include <fcntl.h> // 
#include <stdio.h>//
void	ft_log(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	build_piece(t_filler *f, char *line)
{
	char	*pos;
	int		r;

	if (ft_strncmp(line, "Piece ", 6) != 0)
		return ; //error();
	pos = ft_strchr(line, ' ') + 1;
	if (!(ft_isdigit(*pos)))
		return ; //ERROR
	f->piece.ymax = ft_atoi(pos);
	pos = ft_strchr(pos, ' ') + 1;
	if (!(ft_isdigit(*pos)))
		return ; //error
	f->piece.xmax = ft_atoi(pos);
	if (!(f->piece.tab = (char**)malloc(sizeof(char*) * f->piece.ymax)))
		return ; //ERREUR
	r = -1;
	while (++r < f->piece.ymax)
	{
		if (!(f->piece.tab[r] = (char*)malloc(sizeof(char) * f->piece.xmax)))
			return ; //ERREUR
		get_next_line(0, &(f->piece.tab[r]));
//		ft_log(f->piece.tab[r], f->fd);
	}
}

void	init_turn(t_filler *f)
{
	f->x = 0;
	f->y = 0;
	f->piece.x = 0;
	f->piece.y = 0;
	f->bestpos.n = 0;
}

void	init_filler(t_filler *f)
{
	f->player = '\0';
	f->ennemy = '\0';
	f->strategy = 0;
	f->piece.tab = NULL;
	f->tab = NULL;
	f->tactic[0] = &check_area;
	f->tactic[1] = &check_contact;
	f->bestpos.count_change_strat = 0;
}	

/*void	free_piece_tab(t_piece *p)
{
	int i;

	if (p->piece)
	{
		i = 0;
		while (i < p->ymax)
		{
			free(p->piece[i]);
			i++;
		}
	}
	//ft_memdel((void**)p->piece);
}*/



void	parse_first_time(t_filler *f, char *line)
{
	char **plateau_line;
	
	if ((get_next_line(0, &line) != 1))
		return ; //error
	if (ft_strncmp("$$$ exec p1", line, 11) == 0)
		f->player = 'O';
	else if (ft_strncmp("$$$ exec p2", line, 11) == 0)
		f->player = 'X';
	else
		return ; //error
	ft_strdel(&line);
	if ((get_next_line(0, &line) != 1))
		return ; //error
	if (ft_strncmp("Plateau ", line, 8) == 0)
	{
		if (!(plateau_line = ft_strsplit(line, ' ')))
			return ; //error
		ft_strdel(&line);
		if (!(plateau_line[1] && plateau_line[2]))
			return ; //error();
		f->ymax = ft_atoi(plateau_line[1]);
		f->xmax = ft_atoi(plateau_line[2]);
		if (!(f->ymax >= 2 || f->xmax >= 2))
			return ; //error();
	//	ft_tabdel((void**)plateau_line, -1);
	}
	else
		return ; //error
	 // line with 01234567890123 if everything is as planned
}

/*
** init_free_tab mallocs f->tab if it doesn't exist,
** and free every line for further use
*/

void	init_free_tab(t_filler *f)
{
	int i;

	if (!(f->tab))
	{
		if(!(f->tab = (char**)malloc(sizeof(char*) * f->ymax)))
			return ; //error
	}
	else
	{
		i = 0;
		while (i < f->ymax)
		{
			ft_strdel(&(f->tab[i]));
			i++;
		}
	}
}

void	parse_tab(t_filler *f, char *line)
{
	int		row;
	char	**tab;

	if (!f->player)
		parse_first_time(f, line);
	init_free_tab(f);
	get_next_line(0, &line); //lecture line 012345674152058
	ft_strdel(&line); // del line 01234567890123 if we didn't mess up 
	row = -1;
	while (++row < f->ymax)
	{
		get_next_line(0, &line);
		if (!(tab = ft_strsplit(line, ' ')))
			return ; //error
		ft_strdel(&line);
		if (ft_atoi(tab[0]) != row)
			return ; //error
		f->tab[row] = tab[1];
		//ft_tabdel((void**)tab, 1);	
	}
}

int main(int ac, char **av)
{
	char		*line;
	t_filler	f;
	int16_t		n;

	//sert a rien
	if (!(av))
		return (ac);
	//- ---- --- 
	f.fd = open("/Users/tbehra/Documents/projects/Algo_m/filler/log",
			O_CREAT | O_WRONLY | O_TRUNC);
	line = ft_strdup("abc");
	
	init_filler(&f);
	n = -1;
	while (n)
	{	
		init_turn(&f);
		parse_tab(&f, line);
		get_next_line(0, &line);
		build_piece(&f, line);
		if (!(n = best_placement(&f)))
			break ;	
		ft_printf("%i %i\n", f.bestpos.y, f.bestpos.x);
		//ft_tabdel((void**)f.piece.tab, f.piece.ymax);
		while (get_next_line(0, &line) == 0)
			;
		ft_strdel(&line); // del line Plateau X X
	}
	ft_printf("0 0\n");
	//close(log_fd);
	return (0);
}
