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

void	new_process(t_core *core, int pos, int player)
{
	t_process	*process;
	t_process	*last;

	process = (t_process*)ft_memalloc(sizeof(t_process));
	process->player = player;
	process->pc = pos;
	last = core->process;
	if (!core->process)
		core->process = process;
	else
	{
		while (last->next)
			last = last->next;
		last->next = process;
	}
}
