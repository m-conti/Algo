/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:45:26 by mconti            #+#    #+#             */
/*   Updated: 2018/06/17 14:03:34 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	new_process(t_core *core, int pos, int player, t_reg reg[REG_NUMBER])
{
	t_process	*process;

	process = (t_process*)ft_memalloc(sizeof(t_process));
	process->carry = 0;
	process->lives = 0;
	process->process_time = 0;
	process->to_launch = 0;
	process->jump = 0;
	process->player = player;
	process->pc = pos < 0 ? pos + MEM_SIZE : pos % MEM_SIZE;
	ft_memcpy(process->reg, reg, sizeof(t_reg) * (REG_NUMBER));
	process->next = core->process;
	core->process = process;
}

void	process_to_die(t_core *core)
{
	t_process	*process;
	t_process	*tmp;

	while(core->process && !core->process->lives)
	{
		tmp = core->process->next;
		free(core->process);
		core->process = tmp;
	}
	if (core->process)
		core->process->lives = 0;
	process = core->process;
	while (process && process->next)
	{
		if (!process->next->lives)
		{
			tmp = process->next->next;
			free(process->next);
			process->next = tmp;
		}
		else
			process->next->lives = 0;
		process = process->next;
	}
}

int		overflow(uint16_t pc, uint16_t off_set)
{
	uint16_t	ret;
	int			r;
	int			p;

	p = pc;
	ret = pc + off_set;
	r = (ret - pc) % MEM_SIZE;
	r %= IDX_MOD;
	if (p - IDX_MOD < 0)
		return ( MEM_SIZE - r);
	return (r);
}
