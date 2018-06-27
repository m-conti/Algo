/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:21:01 by mconti            #+#    #+#             */
/*   Updated: 2018/06/27 14:36:02 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ld(t_core *core, t_process *proc)
{
	if (proc->param_type[0] == IND_CODE)
		proc->param[0] = read_arena(core, proc,
			overflow(proc->pc, (int16_t)proc->param[0]),
			DIR_SIZE);
	proc->reg[proc->param[1] - 1] = proc->param[0];
	if (!proc->param[0])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_ldi(t_core *core, t_process *proc)
{
	int addr;

	if (proc->param_type[0] == REG_CODE)
		proc->param[0] = proc->reg[proc->param[0] - 1];
	else if (proc->param_type[0] == IND_CODE)
		proc->param[0] = read_arena(core, proc,
		overflow(proc->pc, (int16_t)proc->param[0]),
		DIR_SIZE);
	else
		proc->param[0] = (int16_t)proc->param[0];
	if (proc->param_type[1] == REG_CODE)
		proc->param[1] = proc->reg[proc->param[1] - 1];
	else
		proc->param[1] = (int16_t)proc->param[1];
	addr = proc->param[0] + proc->param[1];
	proc->reg[proc->param[2] - 1] = read_arena(core, proc,
		overflow(proc->pc, addr), DIR_SIZE);
}

void	op_lld(t_core *core, t_process *proc)
{
	if (proc->param_type[0] == IND_CODE)
		proc->param[0] = read_arena(core, proc, (int16_t)proc->param[0],
			DIR_SIZE);
	proc->reg[proc->param[1] - 1] = proc->param[0];
	if (!proc->param[0])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_lldi(t_core *core, t_process *proc)
{
	int			addr;
	uint32_t	to_load;

	if (proc->param_type[0] == REG_CODE)
		proc->param[0] = proc->reg[proc->param[0] - 1];
	else if (proc->param_type[0] == IND_CODE)
		proc->param[0] = read_arena(core, proc,
			overflow(proc->pc, proc->param[0]),
			DIR_SIZE);
	if (proc->param_type[1] == REG_CODE)
		proc->param[1] = proc->reg[proc->param[1] - 1];
	addr = (proc->param[0] + proc->param[1]) % MEM_SIZE;
	to_load = read_arena(core, proc,
			(addr + proc->pc < 0 ? MEM_SIZE + addr : addr),
			DIR_SIZE);
	proc->reg[proc->param[2] - 1] = to_load;
	if (!to_load)
		proc->carry = 1;
	else
		proc->carry = 0;
}
