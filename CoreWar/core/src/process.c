/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:45:26 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 22:24:18 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*do_process(t_core *core, t_process *current_process)
{
	uint8_t			o;

	if (!current_process->to_launch)
	{
		if (in_hex(o = read_arena(core, current_process, 0, 1)))
		{
			current_process->to_launch = o;
			current_process->process_time = g_op_tab[o - 1].cycle_to_launch - 1;
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

void		new_process(t_core *core, int p, int player, t_reg reg[REG_NUMBER])
{
	t_process	*process;

	if (!(process = (t_process*)ft_memalloc(sizeof(t_process))))
	{
		if (core->opt & VISU)
			endwin();
		error(MALLOC_ERROR);
	}
	process->carry = 0;
	process->lives = 0;
	process->process_time = 0;
	process->to_launch = 0;
	process->jump = 0;
	process->player = player;
	process->pc = p < 0 ? p + MEM_SIZE : p % MEM_SIZE;
	ft_memcpy(process->reg, reg, sizeof(t_reg) * (REG_NUMBER));
	process->next = core->process;
	core->process = process;
	core->nb_process++;
}

void		kill_process(t_core *core)
{
	t_process *tmp;

	tmp = core->process->next;
	free(core->process);
	core->nb_process--;
	core->process = tmp;
}

void		process_to_die(t_core *core)
{
	t_process	*process;
	t_process	*tmp;

	core->cur_proc = NULL;
	while (core->process && !core->process->lives)
		kill_process(core);
	if (core->process)
		core->process->lives = 0;
	process = core->process;
	while (process && process->next)
	{
		if (!process->next->lives)
		{
			tmp = process->next->next;
			free(process->next);
			core->nb_process--;
			process->next = tmp;
		}
		else
		{
			process->next->lives = 0;
			process = process->next;
		}
	}
}

int			overflow(int16_t pc, int off_set)
{
	off_set %= IDX_MOD;
	return (off_set + pc < 0 ? MEM_SIZE + off_set : off_set);
}
