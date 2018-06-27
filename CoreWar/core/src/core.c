/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:36:10 by mconti            #+#    #+#             */
/*   Updated: 2018/06/20 11:21:36 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_winner(t_core *core, uint8_t n)
{
	nodelay(stdscr, FALSE);
	attron(COLOR_PAIR(COLOR_PAIR_P1 + n));
	mvprintw(Y_MSG + 2, X_MSG + 30, "Le joueur \" %s \" a gagné !",
		core->player[n].header.prog_name);
	attroff(COLOR_PAIR(COLOR_PAIR_P1 + n));
	getch();
	endwin();
}

void		is_winner(t_core *core)
{
	uint8_t			i;
	uint32_t		cycle;
	uint8_t			n;
	const int8_t	color[4] = {32, 34, 31, 33};

	cycle = 0;
	i = 0;
	n = 0;
	while (i < core->nb_player)
		if (core->player[i++].last_alive > cycle)
		{
			cycle = core->player[i - 1].last_alive;
			n = i - 1;
		}
	if (core->opt_num_player)
		ft_putchar('\n');
	if (core->opt & VISU)
		print_winner(core, n);
	else if (core->opt & ACTIVE_DUMP)
		print_dump(core);
	else
		ft_printf("Le joueur \" \x1b[%im%s\x1b[0m \" a gagné !\n", color[n],
			core->player[n].header.prog_name);
}

void		change_cycle(t_core *core)
{
	core->current_cycle = 0;
	process_to_die(core);
	if (core->live >= NBR_LIVE || core->checks == MAX_CHECKS)
	{
		core->checks = 0;
		core->cycle_to_die -= CYCLE_DELTA;
	}
	else
		core->checks++;
}

void		corewar(t_core *core)
{
	t_process		*current_process;

	if (core->opt & VISU)
		init_visu(core);
	while (core->cycle_to_die <= CYCLE_TO_DIE)
	{
		if (core->opt & ACTIVE_DUMP && core->current_cycle == core->opt_dump)
			break ;
		if (core->opt & VISU)
			print_arena(core);
		core->cycle++;
		core->current_cycle++;
		current_process = core->process;
		while (current_process)
			current_process = do_process(core, current_process);
		if (core->current_cycle == core->cycle_to_die)
		{
			change_cycle(core);
			if (!core->live)
				break ;
			core->live = 0;
		}
	}
	is_winner(core);
	free_all(core);
}
