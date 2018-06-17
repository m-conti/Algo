/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:21:01 by mconti            #+#    #+#             */
/*   Updated: 2018/06/16 17:37:27 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ld(t_core *core, t_process *proc)
{
	if (proc->param_type[0] == IND_CODE)
		proc->param[0] = read_arena(core, proc,
			overflow(proc->pc, proc->param[0]),
			DIR_SIZE);
	proc->reg[proc->param[1] - 1] = proc->param[0];
	if (!proc->param[0])
		proc->carry = 1;
	else
		proc->carry = 0;
}

/*
** Je ne suis pas sur si pour les indirects on ne doit pas overflow pour l'addition des 2 address si celle-ci dépasse un short
*/

void	op_ldi(t_core *core, t_process *proc)
{
	uint16_t addr;

	if (proc->param_type[0] == REG_CODE)
		proc->param[0] = proc->reg[proc->param[0] - 1];
	else if (proc->param_type[0] == IND_CODE)
		proc->param[0] = read_arena(core, proc,
			overflow(proc->pc, proc->param[0]),
			DIR_SIZE);
	if (proc->param_type[1] == IND_CODE)
		proc->param[1] = read_arena(core, proc,
			overflow(proc-> pc, proc->param[1]),
			DIR_SIZE);
	addr = proc->param[0] + proc->param[1];
	proc->reg[proc->param[2] - 1] = read_arena(core, proc,
			(((addr + proc->pc) % MEM_SIZE) - proc->pc) % IDX_MOD,
			DIR_SIZE);
	if (!proc->reg[proc->param[2] - 1])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_lld(t_core *core, t_process *proc)
{
	if (proc->param_type[0] & 1)
		proc->param[0] = read_arena(core, proc,
			overflow(proc->pc, proc->param[0]),
			DIR_SIZE);
	proc->reg[proc->param[1] - 1] = proc->param[0];
	if (!proc->param[0])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_lldi(t_core *core, t_process *proc)
{
	uint16_t addr;
	uint32_t to_load;

	if (proc->param_type[0] == REG_CODE)
		proc->param[0] = proc->reg[proc->param[0] - 1];
	else if (proc->param_type[0] == IND_CODE)
		proc->param[0] = read_arena(core, proc,
			overflow(proc->pc, proc->param[0]),
			DIR_SIZE);
	if (proc->param_type[1] == IND_CODE)
		proc->param[1] = read_arena(core, proc,
			overflow(proc->pc, proc->param[1]),
			DIR_SIZE);
	addr = proc->param[0] + proc->param[1];
	to_load = read_arena(core, proc,
			(((addr + proc->pc) % MEM_SIZE) - proc->pc),
			DIR_SIZE);
	proc->reg[proc->param[2] - 1] = to_load;
	if (!to_load)
		proc->carry = 1;
	else
		proc->carry = 0;
}
