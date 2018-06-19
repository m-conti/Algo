/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:53:32 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 22:25:31 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_st(t_core *core, t_process *proc)
{
	if (proc->param_type[1] == IND_CODE)
		write_arena(core, proc,
			overflow(proc->pc, (int16_t)proc->param[1]),
			proc->reg[proc->param[0] - 1]);
	else
		proc->reg[proc->param[1] - 1] = proc->reg[proc->param[0] - 1];
}

void	op_sti(t_core *core, t_process *proc)
{
	int addr;

	if (proc->param_type[1] == REG_CODE)
		proc->param[1] = proc->reg[proc->param[1] - 1];
	else if (proc->param_type[1] == IND_CODE)
		proc->param[1] = read_arena(core, proc,
			overflow(proc->pc, (int16_t)proc->param[1]),
			DIR_SIZE);
	else
		proc->param[1] = (int16_t)proc->param[1];
	if (proc->param_type[2] == REG_CODE)
		proc->param[2] = proc->reg[proc->param[2] - 1];
	else
		proc->param[2] = (int16_t)proc->param[2];
	addr = (int)proc->param[1] + (int)proc->param[2];
	write_arena(core, proc,
			overflow(proc->pc, addr),
			proc->reg[proc->param[0] - 1]);
}

void	op_fork(t_core *core, t_process *proc)
{
	new_process(core, overflow(proc->pc,
		(int16_t)proc->param[0]) + proc->pc, proc->player, proc->reg);
	core->process->carry = proc->carry;
	core->process->lives = proc->lives;
}

void	op_lfork(t_core *core, t_process *proc)
{
	int addr;

	addr = (int16_t)proc->param[0] + proc->pc + MEM_SIZE;
	new_process(core, (addr % MEM_SIZE),
		proc->player, proc->reg);
	core->process->carry = proc->carry;
	core->process->lives = proc->lives;
}

void	op_zjmp(t_core *core, t_process *proc)
{
	(void)core;
	if (proc->carry)
		proc->jump = overflow(proc->pc, (int16_t)proc->param[0]);
}
