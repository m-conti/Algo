/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:53:32 by mconti            #+#    #+#             */
/*   Updated: 2018/06/14 16:53:34 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_st(t_core *core, t_process *proc)
{
	if (proc->param_type[1] & 2)
		write_arena(core, proc,
			((((int)proc->param[1] + proc->pc) % MEM_SIZE) - proc->pc) % IDX_MOD,
			proc->reg[proc->param[0] - 1]);
	else
		proc->reg[proc->param[1] - 1] = proc->reg[proc->param[0] - 1];
	if (!proc->reg[proc->param[0] - 1])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_sti(t_core *core, t_process *proc)
{
	int addr;

	if (proc->param_type[1] == REG_CODE)
		proc->param[1] = proc->reg[proc->param[1] - 1];
	else if (proc->param_type[1] == IND_CODE)
		proc->param[1] = read_arena(core, proc,
			((((int)proc->param[1] + proc->pc) % MEM_SIZE) - proc->pc) % IDX_MOD,
			DIR_SIZE);
	if (proc->param_type[2] == IND_CODE)
		proc->param[2] = read_arena(core, proc,
			((((int)proc->param[2] + proc->pc) % MEM_SIZE) - proc->pc) % IDX_MOD,
			DIR_SIZE);
	addr = proc->param_type[1] + proc->param_type[2];
	write_arena(core, proc,
			(((addr + proc->pc) % MEM_SIZE) - proc->pc) % IDX_MOD,
			proc->reg[proc->param[0] - 1]);
	if (proc->reg[proc->param[0] - 1])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_fork(t_core *core, t_process *proc)
{
	new_process(core, (((((int)proc->param[1] + proc->pc) % MEM_SIZE) - proc->pc)
		% IDX_MOD) + proc->pc, proc->player, proc->reg);
}

void	op_lfork(t_core *core, t_process *proc)
{
	new_process(core, ((int)proc->param[1] + proc->pc) % MEM_SIZE,
		proc->player, proc->reg);
}

void	op_zjmp(t_core *core, t_process *proc)
{
	(void)core;
	if (proc->carry)
		proc->jump = proc->param[0];
}
