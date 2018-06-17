/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:53:32 by mconti            #+#    #+#             */
/*   Updated: 2018/06/16 17:28:40 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_st(t_core *core, t_process *proc)
{
	if (proc->param_type[1] == IND_CODE)
		write_arena(core, proc,
			overflow(proc->pc, proc->param[1]),
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
			overflow(proc->pc, proc->param[1]),
			DIR_SIZE);
	if (proc->param_type[2] == REG_CODE)
		proc->param[2] = proc->reg[proc->param[2] - 1];
	addr = proc->param[1] + proc->param[2];
	write_arena(core, proc,
			overflow(proc->pc, addr),
			proc->reg[proc->param[0] - 1]);
}

void	op_fork(t_core *core, t_process *proc)
{
	new_process(core, overflow(proc->pc, proc->param[0]) + proc->pc, proc->player, proc->reg);
}

void	op_lfork(t_core *core, t_process *proc)
{
	new_process(core, (proc->param[0] + proc->pc) % MEM_SIZE,
		proc->player, proc->reg);
}

void	op_zjmp(t_core *core, t_process *proc)
{
	(void)core;
	if (proc->carry)
		proc->jump = proc->param[0];
}
