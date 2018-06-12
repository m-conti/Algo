/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/12 17:45:41 by tbehra           ###   ########.fr       */
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
	
	mvaddch(2 + row, 0, '*');
	while (i < v->n_char_row)
	{
		mvprintw(2 + row, 3 + i * 3, "%.2x ", arena[(row * v->n_char_row)+i]);
		i++;
	}
	if (v->ncol >= N_CHAR_ROW_MAX * 3 + 4)
		mvaddch(2 + row, N_CHAR_ROW_MAX * 3 + 4, '*');
}

void	init_visu(t_visu *v)
{
	int offset_col;

	initscr();
	offset_col = 6;
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
	init_visu(&visu);
	i = -1;
	while (++i < visu.ncol)
		mvaddch(0, i, '*');
	mvaddch(1, 0, '*');
	if (visu.ncol >= N_CHAR_ROW_MAX * 3 + 4)
		mvaddch(1, N_CHAR_ROW_MAX * 3 + 4, '*');
	i = -1;
	while (++i < visu.n_displayed_lines)
		print_line(arena, i, &visu);

	if (visu.nrow >= visu.n_displayed_lines + 2)
	{
		mvaddch(visu.n_displayed_lines + 2, 0, '*');
		if (visu.ncol >= N_CHAR_ROW_MAX * 3 + 4)
			mvaddch(visu.n_displayed_lines + 2, N_CHAR_ROW_MAX * 3 + 4, '*');
		i = -1;
		while (++i < visu.ncol)
			mvaddch(visu.n_displayed_lines + 3, i, '*');
	}
	raw();
	keypad(stdscr, TRUE);		
	noecho();			
	refresh();			
	getch();			
	endwin();			

	return (0);
}
