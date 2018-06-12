/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/12 15:31:32 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "../includes/libft.h"


#define N_CHAR_ROW_MAX 64
#define N_LINES_MAX 64
//compilation :  gcc <program file> -lncurses
//
//gcc visu.c -lncurses ~/Documents/projects/libft/libft.a

typedef struct		s_visu
{
	int				nrow;
	int				ncol;
	int				n_displayed_lines;
	int				n_char_row;
}					t_visu;


void print_line(unsigned char *arena, int row, t_visu *v)
{
	int i;

	i = 0;
	while (i < v->n_char_row)
	{
		mvprintw(row, i * 3, "%.2x ", arena[(row * v->n_char_row)+i]);
		i++;
	}
}

void	init_visu(t_visu *v)
{
	getmaxyx(stdscr, v->nrow, v->ncol);
	v->n_displayed_lines = (v->nrow > N_LINES_MAX) ? N_LINES_MAX : v->nrow;
	v->n_char_row = (v->ncol / 3 > N_CHAR_ROW_MAX) ? N_CHAR_ROW_MAX : v->ncol / 3;
}

int main()
{
	int ch;
	unsigned char arena[4096];
	t_visu visu;
	int n_lines;

	int i = 0;
	while (i < 4096)
	{
		if (i < 610 || (i >= 2048 && i < 2658))
			arena[i] = ((i*(i+252))%3 + i*124) % 255;
		else
			arena[i] = 0;
		i++;
	}

	initscr();			
	init_visu(&visu);
	
	i = -1;
	while (++i < visu.n_displayed_lines)
		print_line(arena, i, &visu);
//	mvprintw(visu.nrow/2,(visu.ncol-ft_strlen(mesg))/2,"%s", line);
 	
	raw();
	keypad(stdscr, TRUE);		
	noecho();			
	refresh();			
	getch();			
	endwin();			

	return 0;
}
