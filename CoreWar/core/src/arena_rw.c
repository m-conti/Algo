/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_rw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 23:43:12 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/19 23:45:53 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		increase_pc(t_process *proc, int how_much)
{
	proc->pc = (proc->pc + how_much) % MEM_SIZE;
}

uint8_t		in_hex(uint8_t nb)
{
	return (nb >= 1 && nb <= 16);
}

uint32_t	read_arena(t_core *core, t_process *proc, int offset,
		int size_to_read)
{
	uint32_t	res;
	int			i;

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

void		write_arena(t_core *core, t_process *proc, int offset,
		uint32_t to_write)
{
	int i;

	i = 4;
	while (--i >= 0)
	{
		core->arena[(proc->pc + offset + i) % MEM_SIZE] = to_write & 0xFF;
		core->v.colors[(proc->pc + offset + i) % MEM_SIZE] =
			proc->player + COLOR_PAIR_P1;
		to_write >>= 0x8;
	}
}

void		free_all(t_core *core)
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
