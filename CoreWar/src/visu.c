/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/16 14:58:36 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
		mvprintw(2 + row, 3 + i * 3, "%.2x",
				core->arena[(row * core->v.n_char_row) + i]);
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
	init_color(COLOR_LBLUE, 500, 500, 900); 
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_PAIR_P1, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_PAIR_P2, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_PAIR_P3, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_PAIR_P4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_PROCESS_P1, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_PROCESS_P2, COLOR_BLACK, COLOR_LBLUE);
	init_pair(COLOR_PROCESS_P3, COLOR_BLACK, COLOR_RED);
	init_pair(COLOR_PROCESS_P4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_BORDER, COLOR_GRAY, COLOR_GRAY);
}

void	init_visu(t_core *core)
{
	int offset_col;

	initscr();
	start_color();
	curs_set(0);
	nodelay(stdscr, TRUE);
	init_color_pairs();
	offset_col = 6;
	getmaxyx(stdscr, core->v.nrow, core->v.ncol);
	//ATTENTION FAUT PEUT ETRE REFAIRE TOURNER CA APRES INIT VISU
	core->v.n_displayed_lines = (core->v.nrow > N_LINES_MAX) ? N_LINES_MAX : core->v.nrow;
	core->v.n_char_row = ((core->v.ncol - offset_col) / 3 > N_CHAR_ROW_MAX)
		? N_CHAR_ROW_MAX : (core->v.ncol - offset_col) / 3;
	init_colors_visu(core);
	core->v.old_process = NULL;
	core->v.delay = 1000;
	core->v.pause = 0;
	toggle_pause(core);
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

void	add_old_proc(t_old_proc **old_proc, int pos, uint8_t color)
{
	t_old_proc *new;
	t_old_proc *cur;

	new = (t_old_proc*)malloc(sizeof(t_old_proc));
	new->pos = pos;
	new->col = color;
	new->next = NULL;
	if (!(*old_proc))
		*old_proc = new;
	else
	{
		cur = *old_proc;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

void	put_processes(t_core *core)
{
	t_process *cur;
	t_old_proc *cur_old;
	t_old_proc *tmp_old;

	if	(core->v.old_process != NULL)
	{
		cur_old = core->v.old_process;
		while (cur_old)
		{
			tmp_old = cur_old;
			core->v.colors[cur_old->pos] = cur_old->col;
			cur_old = cur_old->next;
			free(cur_old);
		}
		core->v.old_process = NULL;
	}
	cur = core->process;
	core->v.nb_process = 0;
	while (cur)
	{
		core->v.colors[cur->pc] = COLOR_PROCESS_P1 + cur->player; 
		add_old_proc(&(core->v.old_process), cur->pc, COLOR_PAIR_P1 + cur->player);
		cur = cur->next;
		core->v.nb_process++;
	}
}

void	show_alive(char *player_name)
{
	mvprintw(Y_MSG, 3, "un processus dit que le joueur \"%s\" est en vie", player_name);
}

void	print_state(t_core *core)
{
	unsigned int i_player;

	mvprintw(Y_CYCLE, X_CYCLE, "Cycle : %d", core->cycle);
	mvprintw(Y_CYCLE + 2, X_CYCLE, "Process : %d", core->v.nb_process);
	i_player = 0;
	while (i_player < core->nb_player)
	{
		mvprintw(Y_CYCLE + 4 + 2 * i_player, X_CYCLE, "Player %d : %s",
				core->player[i_player].nbr, core->player[i_player].header.prog_name);
		i_player++;
	}	
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
	deal_key(core, ch);
	usleep(core->v.delay);
	while (core->v.pause)
	{
		ch = getch();			
		deal_key(core, ch);
		if (core->v.pause == -1)
		{
			core->v.pause = 1;
			break ;
		}
	}
	return (0);
}
