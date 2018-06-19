/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:39:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/19 22:01:25 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void	show_alive(t_core *core, t_process *proc, uint8_t i)
{
	static uint32_t	len = 0;
	uint8_t			j;

	j = 0;
	if (!len)
		while (j < core->nb_player)
			len = len > ft_strlen(core->player[j++].header.prog_name) ? len :
				ft_strlen(core->player[j - 1].header.prog_name) + 1;
	if (len > 20)
		len = 20;
	mvprintw(Y_MSG, X_MSG, "un processus du joueur \" ");
	attron(COLOR_PAIR(COLOR_PAIR_P1 + proc->player));
	mvprintw(Y_MSG, X_MSG + 25, "%-20.20s",
			core->player[proc->player].header.prog_name);
	attroff(COLOR_PAIR(COLOR_PAIR_P1 + proc->player));
	mvprintw(Y_MSG, X_MSG + 25 + len, " \" que le joueur \" ");
	attron(COLOR_PAIR(COLOR_PAIR_P1 + i));
	mvprintw(Y_MSG, X_MSG + 44 + len, "%-20.20s",
			core->player[i].header.prog_name);
	attroff(COLOR_PAIR(COLOR_PAIR_P1 + i));
	mvprintw(Y_MSG, X_MSG + 44 + len * 2, " \" est en vie");
}

void	print_players(t_core *core)
{
	unsigned int	i_player;

	i_player = 0;
	while (i_player < core->nb_player)
	{
		attron(COLOR_PAIR(COLOR_PAIR_P1 + i_player));
		mvprintw(Y_CYCLE + 10 + 3 * i_player, X_CYCLE, "Player %d: ",
				i_player + 1);
		attroff(COLOR_PAIR(COLOR_PAIR_P1 + i_player));
		mvprintw(Y_CYCLE + 10 + 3 * i_player, X_CYCLE + 10, "%s (%x)",
				core->player[i_player].header.prog_name,
				core->player[i_player].nbr);
		mvprintw(Y_CYCLE + 11 + 3 * i_player, X_CYCLE + 10,
				"Last alive: %u", core->player[i_player].last_alive);
		i_player++;
	}
}

void	print_state(t_core *core)
{
	int i;

	attron(COLOR_PAIR(COLOR_BORDER));
	i = X_DEMARC - 1;
	while (++i <= core->v.ncol)
		mvaddch(Y_DEMARC, i, '*');
	attroff(COLOR_PAIR(COLOR_BORDER));
	mvprintw(Y_CYCLE, X_CYCLE, "Cycle : %d", core->cycle);
	mvprintw(Y_CYCLE + 2, X_CYCLE, "Cycle_to_die: %d                  ",
			core->cycle_to_die);
	mvprintw(Y_CYCLE + 4, X_CYCLE, "Current_cycle: %d                 ",
			core->current_cycle);
	mvprintw(Y_CYCLE + 6, X_CYCLE, "Number of processes: %d           ",
			core->nb_process);
	mvprintw(Y_CYCLE + 8, X_CYCLE, "Delay between cycles (ms): %d     ",
			core->v.delay / 1000);
	print_players(core);
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
