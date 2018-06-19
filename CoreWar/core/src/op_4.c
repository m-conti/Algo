/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:48:51 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 22:25:18 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_add(t_core *core, t_process *proc)
{
	(void)core;
	proc->reg[proc->param[2] - 1] =
		proc->reg[proc->param[0] - 1] + proc->reg[proc->param[1] - 1];
	if (!proc->reg[proc->param[2] - 1])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_sub(t_core *core, t_process *proc)
{
	(void)core;
	proc->reg[proc->param[2] - 1] =
		proc->reg[proc->param[0] - 1] - proc->reg[proc->param[1] - 1];
	if (!proc->reg[proc->param[2] - 1])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_and(t_core *core, t_process *proc)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (proc->param_type[i] == REG_CODE)
			proc->param[i] = proc->reg[proc->param[i] - 1];
		else if (proc->param_type[i] == IND_CODE)
			proc->param[i] = read_arena(core, proc,
				overflow(proc->pc, (int16_t)proc->param[i]),
				DIR_SIZE);
		i++;
	}
	proc->reg[proc->param[2] - 1] = proc->param[0] & proc->param[1];
	if (!proc->reg[proc->param[2] - 1])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_or(t_core *core, t_process *proc)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (proc->param_type[i] == REG_CODE)
			proc->param[i] = proc->reg[proc->param[i] - 1];
		else if (proc->param_type[i] == IND_CODE)
			proc->param[i] = read_arena(core, proc,
				overflow(proc->pc, (int16_t)proc->param[i]),
				DIR_SIZE);
		i++;
	}
	proc->reg[proc->param[2] - 1] = proc->param[0] | proc->param[1];
	if (!proc->reg[proc->param[2] - 1])
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_xor(t_core *core, t_process *proc)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (proc->param_type[i] == REG_CODE)
			proc->param[i] = proc->reg[proc->param[i] - 1];
		else if (proc->param_type[i] == IND_CODE)
			proc->param[i] = read_arena(core, proc,
				overflow(proc->pc, (int16_t)proc->param[i]),
				DIR_SIZE);
		i++;
	}
	proc->reg[proc->param[2] - 1] = proc->param[0] ^ proc->param[1];
	if (!proc->reg[proc->param[2] - 1])
		proc->carry = 1;
	else
		proc->carry = 0;
}
