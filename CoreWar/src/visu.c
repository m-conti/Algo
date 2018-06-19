/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/19 17:32:21 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_line(t_core *core, int row)
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
	while (++i < core->v.ncol)
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
	t_process	*cur;
	
	cur = core->process;
	while (cur)
	{
		if (core->v.ncol >= MIN_COL_DISPLAY && core->v.nrow >= MIN_ROW_DISPLAY)
		{
			attron(COLOR_PAIR(COLOR_PROCESS_P1 + cur->player));	
			mvprintw(2 + (cur->pc / core->v.n_char_row), 3 +
				(cur->pc % core->v.n_char_row) * 3, "%.2x",
				core->arena[cur->pc]);
			attroff(COLOR_PAIR(COLOR_PROCESS_P1 + cur->player));
		}
		cur = cur->next;
	}
}

void	show_alive(char *player_name)
{
	mvprintw(Y_MSG, 3, "un processus dit que le joueur \"%s\" est en vie",
			player_name);
}

void	print_state(t_core *core)
{
	unsigned int	i_player;
	int				i;

	attron(COLOR_PAIR(COLOR_BORDER));
	i = X_DEMARC - 1;
	while (++i <= core->v.ncol)
		mvaddch(Y_DEMARC, i, '*');
	attroff(COLOR_PAIR(COLOR_BORDER));
	mvprintw(Y_CYCLE, X_CYCLE, "Cycle : %d", core->cycle);
	mvprintw(Y_CYCLE + 1, X_CYCLE, "Cycle_to_die : %d          ",
		core->cycle_to_die);
	mvprintw(Y_CYCLE + 2, X_CYCLE, "Current_cycle : %d         ",
		core->current_cycle);
	mvprintw(Y_CYCLE + 3, X_CYCLE, "Process : %d               ",
		core->nb_process);
	i_player = 0;
	while (i_player < core->nb_player)
	{
		mvprintw(Y_CYCLE + 4 + 2 * i_player, X_CYCLE, "Player %d : %s",
			core->player[i_player].nbr,
			core->player[i_player].header.prog_name);
		i_player++;
	}
}

int		print_arena(t_core *core)
{
	int i;
	int ch;

	print_two_first_lines(core);
	i = -1;
	while (++i < core->v.n_displayed_lines)
		print_line(core, i);
	print_two_last_lines(core);
	print_state(core);
	put_processes(core);
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
