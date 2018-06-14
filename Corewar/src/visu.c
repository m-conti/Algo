/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/12 20:02:15 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define N_CHAR_ROW_MAX 64
#define N_LINES_MAX 64

#define COLOR_PAIR_P1 2
#define COLOR_PAIR_P2 3
#define COLOR_PAIR_P3 4
#define COLOR_PAIR_P4 5

typedef struct		s_visu
{
	int				nrow;
	int				ncol;
	int				n_displayed_lines;
	int				n_char_row;
	uint8_t			colors[MEM_SIZE];
}					t_visu;

void print_line(t_core *core, int row)
{
	int	i;

	i = 0;
	mvaddch(2 + row, 0, '*');
	while (i < core->v->n_char_row)
	{
		attron(COLOR_PAIR(core->v->colors[(row * core->v->n_char_row) + i]));
		mvprintw(2 + row, 3 + i * 3, "%.2x ", core->arena[(row * core->v->n_char_row) + i]);
		attroff(COLOR_PAIR(core->v->colors[(row * core->v->n_char_row) + i]));
		i++;
	}
	if (core->v->ncol >= N_CHAR_ROW_MAX * 3 + 4)
		mvaddch(2 + row, N_CHAR_ROW_MAX * 3 + 4, '*');
}

void	init_colors_visu(t_core *core, t_visu *v)
{
	unsigned int		i;
	uint8_t	cur_col;

	i = 0;
	cur_col = COLOR_PAIR_P1;
	while (i < MEM_SIZE)
	{
		if ((i == core->player[0].header.prog_size) || (core->nb_player >= 2 &&
			i == MEM_SIZE / core->nb_player + core->player[1].header.prog_size) ||
			(core->nb_player >= 3 && i == (MEM_SIZE / core->nb_player) * 2 +
			core->player[2].header.prog_size) || (core->nb_player == 4 &&
			i == (MEM_SIZE / core->nb_player) * 3 + core->player[3].header.prog_size))
			cur_col = 1;
		if (core->nb_player >= 2 && i == MEM_SIZE / core->nb_player)
			cur_col = COLOR_PAIR_P2;
		if (core->nb_player >= 3 && i == (MEM_SIZE / core->nb_player) * 2)
			cur_col = COLOR_PAIR_P3;
		if (core->nb_player == 4 && i == (MEM_SIZE / core->nb_player) * 3)
			cur_col = COLOR_PAIR_P4;
		v->colors[i] = cur_col;
		i++;
	}
}

void	init_visu(t_core *core, t_visu *v)
{
	int offset_col;

	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_PAIR_P1, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_PAIR_P2, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_PAIR_P3, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_PAIR_P4, COLOR_YELLOW, COLOR_BLACK);
	offset_col = 6;
	getmaxyx(stdscr, v->nrow, v->ncol);
	v->n_displayed_lines = (v->nrow > N_LINES_MAX) ? N_LINES_MAX : v->nrow;
	v->n_char_row = ((v->ncol - offset_col) / 3 > N_CHAR_ROW_MAX)
		? N_CHAR_ROW_MAX : (v->ncol - offset_col) / 3;
	init_colors_visu(core, v);
}

void	print_two_first_lines(t_visu *v)
{
	int i;

	i = -1;
	while (++i < v->ncol)
		mvaddch(0, i, '*');
	mvaddch(1, 0, '*');
	if (v->ncol >= N_CHAR_ROW_MAX * 3 + 4)
		mvaddch(1, N_CHAR_ROW_MAX * 3 + 4, '*');
}

void	print_two_last_lines(t_visu *v)
{
	int i;

	if (v->nrow >= v->n_displayed_lines + 2)
	{
		mvaddch(v->n_displayed_lines + 2, 0, '*');
		if (v->ncol >= N_CHAR_ROW_MAX * 3 + 4)
			mvaddch(v->n_displayed_lines + 2, N_CHAR_ROW_MAX * 3 + 4, '*');
		i = -1;
		while (++i < v->ncol)
			mvaddch(v->n_displayed_lines + 3, i, '*');
	}

}

int print_arena(t_core *core)
{
	t_visu visu;
	int i;

	init_visu(core, &visu);
	print_two_first_lines(&visu);
	i = -1;
	while (++i < visu.n_displayed_lines)
		print_line(core, i, &visu);
	print_two_last_lines(&visu);

	raw();
	keypad(stdscr, TRUE);		
	noecho();			
	refresh();			
	getch();			
	endwin();			

	return (0);
}
