/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:36:10 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 23:46:27 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op_tab.h"

t_process	*do_process(t_core *core, t_process *current_process)
{
	uint8_t			op;

	if (!current_process->to_launch)
	{
		if (in_hex(op = read_arena(core, current_process, 0, 1)))
		{
			current_process->to_launch = op;
			current_process->process_time
				= g_op_tab[op - 1].cycle_to_launch - 1;
		}
		else
			increase_pc(current_process, 1);
	}
	else if (!--current_process->process_time)
	{
		if (check_op(core, current_process))
			do_operator(core, current_process);
		increase_pc(current_process, current_process->jump);
		current_process->to_launch = 0;
	}
	return (current_process->next);
}

void	is_winner(t_core *core)
{
	uint8_t			i;
	uint32_t		cycle;
	uint8_t			n;
	const int8_t	color[4] = {32, 34, 31, 33};

	cycle = 0;
	i = 0;
	while (i < core->nb_player)
	{
		if (core->player[i].last_alive > cycle)
		{
			cycle = core->player[i].last_alive;
			n = i;
		}
		i++;
	}
	if (core->opt & VISU)
	{
		nodelay(stdscr, FALSE);
		attron(COLOR_PAIR(COLOR_PAIR_P1 + n));
		mvprintw(Y_CYCLE + 10, X_CYCLE, "Le joueur \" %s \" a gagné !",
			core->player[n].header.prog_name);
		attroff(COLOR_PAIR(COLOR_PAIR_P1 + n));
		getch();
		endwin();
	}
	else
	{
		if (core->opt_num_player)
			ft_putchar('\n');
		ft_printf("Le joueur \" \x1b[%im%s\x1b[0m \" a gagné !\n", color[n],
			core->player[n].header.prog_name);
	}
}

void	free_all(t_core *core)
{
	t_process	*proc;
	t_process	*tmp;

	proc = core->process;
	while (proc)
	{
		tmp = proc->next;
		free(proc);
		proc = tmp;
	}
}

void	corewar(t_core *core)
{
	t_process		*current_process;
	uint8_t			checks;

	checks = 0;
	while (core->cycle_to_die > 0)
	{
		if (core->opt & VISU)
			print_arena(core);
		core->cycle++;
		core->current_cycle++;
		current_process = core->process;
		while (current_process)
		{
			current_process = do_process(core, current_process);
		}
		if (core->current_cycle == core->cycle_to_die)
		{
			core->current_cycle = 0;
			process_to_die(core);
			if (core->live >= NBR_LIVE || checks == MAX_CHECKS)
			{
				core->cycle_to_die -= CYCLE_DELTA;
				checks = 0;
			}
			else
				checks++;
			if (!core->live)
				break ;
			core->live = 0;
		}
	}
	is_winner(core);
	free_all(core);
}
