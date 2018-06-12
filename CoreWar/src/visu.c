/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/12 16:42:24 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "../includes/libft.h"
#include "../includes/op_struct.h"


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


void print_line(uint8_t arena[MEM_SIZE], int row, t_visu *v)
{
	int i;

	i = 0;
	
	mvaddch(row, 0, '*');
	while (i < v->n_char_row)
	{
		mvprintw(2 + row, 2 + i * 3, "%.2x ", arena[(row * v->n_char_row)+i]);
		i++;
	}
	if (v->ncol >= N_CHAR_ROW_MAX * 3 + 2)
		mvaddch(row, N_CHAR_ROW_MAX * 3 + 2, '*');
}

void	init_visu(t_visu *v)
{
	int offset_col;

	offset_col = 4;
	getmaxyx(stdscr, v->nrow, v->ncol);
	v->n_displayed_lines = (v->nrow > N_LINES_MAX) ? N_LINES_MAX : v->nrow;
	v->n_char_row = ((v->ncol - offset_col) / 3 > N_CHAR_ROW_MAX)
		? N_CHAR_ROW_MAX : (v->ncol - offset_col) / 3;
}

//int print_arena(t_core *core)
int main()
{
	t_visu visu;
	int i;
	uint8_t arena[MEM_SIZE];

	i = 0;
	while (i < MEM_SIZE) 
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
	while (++i < visu.ncol)
		addch('*');
	i = -1;
	while (++i < visu.n_displayed_lines)
		print_line(arena, i, &visu);
 	
	raw();
	keypad(stdscr, TRUE);		
	noecho();			
	refresh();			
	getch();			
	endwin();			

	return (0);
}
