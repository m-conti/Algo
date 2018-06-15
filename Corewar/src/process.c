/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:45:26 by mconti            #+#    #+#             */
/*   Updated: 2018/06/12 18:45:28 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	new_process(t_core *core, int pos, int player, t_reg reg[REG_NUMBER])
{
	t_process	*process;

	process = (t_process*)ft_memalloc(sizeof(t_process));
	process->player = player;
	process->pc = pos;
	ft_memcpy(process->reg, reg, sizeof(t_reg) * (REG_NUMBER + 1));
	process->next = core->process;
	core->process = process;
}

void	process_to_die(t_core *core)
{
	t_process	*process;
	t_process	*tmp;

	while(!core->process->lives)
	{
		tmp = core->process->next;
		free(core->process);
		core->process = tmp;
	}
	core->process->lives = 0;
	process = core->process;
	while (process->next)
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
