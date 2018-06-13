/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/13 21:44:58 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define N_CHAR_ROW_MAX 64
#define N_LINES_MAX 64

#define COLOR_GRAY 50
#define COLOR_PAIR_P1 2
#define COLOR_PAIR_P2 3
#define COLOR_PAIR_P3 4
#define COLOR_PAIR_P4 5
#define COLOR_PROCESS_P1 6
#define COLOR_PROCESS_P2 7
#define COLOR_PROCESS_P3 8
#define COLOR_PROCESS_P4 9
#define COLOR_BORDER 10

void print_line(t_core *core, int row)
{
	int	i;

	i = 0;
	attron(COLOR_PAIR(COLOR_BORDER));
	mvaddch(2 + row, 0, '*');
	attroff(COLOR_PAIR(COLOR_BORDER));
	while (i < core->v.n_char_row)
	{
		attron(COLOR_PAIR(core->v.colors[(row * core->v.n_char_row) + i]));
		mvprintw(2 + row, 3 + i * 3, "%.2x", core->arena[(row * core->v.n_char_row) + i]);
		attroff(COLOR_PAIR(core->v.colors[(row * core->v.n_char_row) + i]));
		mvaddch(2 + row, 3 + i * 3 + 3, ' ');
		i++;
	}
	if (core->v.ncol >= N_CHAR_ROW_MAX * 3 + 4)
	{
		attron(COLOR_PAIR(COLOR_BORDER));
		mvaddch(2 + row, N_CHAR_ROW_MAX * 3 + 4, '*');
		attroff(COLOR_PAIR(COLOR_BORDER));
	}
}

void	init_colors_visu(t_core *core)
{
	unsigned int	i;
	uint8_t			cur_col;

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
		core->v.colors[i] = cur_col;
		i++;
	}
}

void	init_color_pairs()
{
	init_color(COLOR_GRAY, 500, 500, 500); 
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_PAIR_P1, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_PAIR_P2, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_PAIR_P3, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_PAIR_P4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_PROCESS_P1, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_PROCESS_P2, COLOR_BLACK, COLOR_BLUE);
	init_pair(COLOR_PROCESS_P3, COLOR_BLACK, COLOR_RED);
	init_pair(COLOR_PROCESS_P4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_BORDER, COLOR_GRAY, COLOR_GRAY);
}

void	init_visu(t_core *core)
{
	int offset_col;

	initscr();
	start_color();
	init_color_pairs();
	offset_col = 6;
	getmaxyx(stdscr, core->v.nrow, core->v.ncol);
	core->v.n_displayed_lines = (core->v.nrow > N_LINES_MAX) ? N_LINES_MAX : core->v.nrow;
	core->v.n_char_row = ((core->v.ncol - offset_col) / 3 > N_CHAR_ROW_MAX)
		? N_CHAR_ROW_MAX : (core->v.ncol - offset_col) / 3;
	init_colors_visu(core);
}

void	print_two_first_lines(t_core *core)
{
	int i;

	i = -1;
	attron(COLOR_PAIR(COLOR_BORDER));
	while (++i <  core->v.ncol)
		mvaddch(0, i, '*');
	mvaddch(1, 0, '*');
	if (core->v.ncol >= N_CHAR_ROW_MAX * 3 + 4)
		mvaddch(1, N_CHAR_ROW_MAX * 3 + 4, '*');
	attroff(COLOR_PAIR(COLOR_BORDER));
}

void	print_two_last_lines(t_core *core)
{
	int i;

	if (core->v.nrow >= core->v.n_displayed_lines + 2)
	{
		attron(COLOR_PAIR(COLOR_BORDER));
		mvaddch(core->v.n_displayed_lines + 2, 0, '*');
		if (core->v.ncol >= N_CHAR_ROW_MAX * 3 + 4)
			mvaddch(core->v.n_displayed_lines + 2, N_CHAR_ROW_MAX * 3 + 4, '*');
		i = -1;
		while (++i < core->v.ncol)
			mvaddch(core->v.n_displayed_lines + 3, i, '*');
		attroff(COLOR_PAIR(COLOR_BORDER));
	}
}

void	put_processes(t_core *core)
{
	t_process *cur;

	cur = core->process;
	while (cur)
	{
		core->v.colors[cur->pc] = COLOR_PROCESS_P1 + cur->player; 
		cur = cur->next;
	}
}

void	print_state(t_core *core)
{
	(void) core;
	return ;
}

int print_arena(t_core *core)
{
	int i;
	int ch;

	put_processes(core);
	print_two_first_lines(core);
	i = -1;
	while (++i < core->v.n_displayed_lines)
		print_line(core, i);
	print_two_last_lines(core);
	print_state(core);
	raw();
	keypad(stdscr, TRUE);
	noecho();			
	refresh();			
	ch = getch();			
	return (0);
}
