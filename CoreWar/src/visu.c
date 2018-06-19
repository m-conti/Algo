/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/16 15:56:22 by tbehra           ###   ########.fr       */
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

	if (!(new = (t_old_proc*)malloc(sizeof(t_old_proc))))
	{
		endwin();
		error(MALLOC_ERROR);
	}
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

uint8_t	find_old_col(t_core *core, int pos)
{
	t_old_proc *cur;
	
	cur = core->v.old_process;
	while (cur)
	{
		if (cur->pos == pos)
			return (cur->col);
		cur = cur->next;
	}
	return (COLOR_BUG);
}

void	put_processes(t_core *core)
{
	t_process *cur;
	t_old_proc *cur_old;
	t_old_proc *tmp_old;
	uint8_t		old_col;

	if	(core->v.old_process)
	{
		cur_old = core->v.old_process;
		while (cur_old)
		{
			tmp_old = cur_old;
			core->v.colors[cur_old->pos] = cur_old->col;
			cur_old = cur_old->next;
			free(tmp_old);
		}
		core->v.old_process = NULL;
	}
	cur = core->process;
	while (cur)
	{
		//
		if (cur->carry)
			mvprintw(4, 200, "carry = 1");
		else
			mvprintw(4, 200, "carry = 0");

		//
		old_col = core->v.colors[cur->pc];
		if (old_col >= COLOR_PROCESS_P1 && old_col <= COLOR_PROCESS_P4)
			old_col = find_old_col(core, cur->pc);
		add_old_proc(&(core->v.old_process), cur->pc, old_col);
		core->v.colors[cur->pc] = COLOR_PROCESS_P1 + cur->player; 
		cur = cur->next;
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
	mvprintw(Y_CYCLE + 1, X_CYCLE, "Cycle_to_die : %d          ", core->cycle_to_die);
	mvprintw(Y_CYCLE + 2, X_CYCLE, "Current_cycle : %d         ", core->current_cycle);
	mvprintw(Y_CYCLE + 3, X_CYCLE, "Process : %d               ", core->nb_process);
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
