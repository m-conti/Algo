/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:36:10 by mconti            #+#    #+#             */
/*   Updated: 2018/06/14 11:07:18 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op_tab.h"

void    increase_pc(t_process *proc, int how_much)
{
	proc->pc = (proc->pc + how_much) % MEM_SIZE;
}

uint8_t	in_hex(uint8_t nb)
{
	return (nb >= 1 && nb <= 16);
}

int		read_arena(t_core *core, t_process *proc, int offset, int size_to_read)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (i < size_to_read)
	{
		res <<= 8;
		res += core->arena[(proc->pc + offset + i) % MEM_SIZE];
			i++;
	}
	return (res);
}

void	do_process(t_core *core, t_process *current_process)
{
	uint8_t			op;

	if (!current_process->to_launch)
	{
		if (in_hex(op = read_arena(core, current_process, 0, 1)))
		{
			current_process->to_launch = op;
			current_process->process_time = g_op_tab[op - 1].cycle_to_launch;
		}
		else
			increase_pc(current_process, 1);
	}
	else if (!--current_process->process_time)
	{
		if (check_op(core, current_process))
			core->fc_op[current_process->to_launch](core, current_process);
		increase_pc(current_process, current_process->jump);
		current_process->to_launch = 0;
	}
}

void	corewar(t_core *core)
{
	t_process		*current_process;
	uint8_t			checks;

	checks = 0;
	while (core->cycle_to_die > 0)
	{
		print_arena(core);
		core->cycle++;
		core->current_cycle++;
		current_process = core->process;
		while (current_process)
			; //do_process(core, current_process);
		if (core->current_cycle == core->cycle_to_die)
		{
			core->cycle = 0;
			if (core->live > NBR_LIVE || checks == MAX_CHECKS)
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
}
