/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:36:10 by mconti            #+#    #+#             */
/*   Updated: 2018/06/12 18:36:11 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void    increase_pc(t_process *proc, int how_much)
{
	(proc->pc += how_much) % MEM_SIZE;
}

int		in_hex(int nb)
{
	return (nb >= 1 && nb <= 16);
}

void	do_process(t_core *core, t_process *current_process)
{
	uint8_t			param;

	if (!current_process->to_launch)
	{
		if (in_hex(param = read_arena(core, current_process, 0, 1)))
		{
			current_process->to_launch = param;
			current_process->process_time = op_tab[param - 1];
		}
		else
			increase_pc(current_process, 1);
	}
	else if (!--current_process->process_time)
	{
		if (check_op(core, current_process))
			core->fc_op[current_process->to_launch](core, current_process);
		increase_pc(current_process, current_process->jump);
		current_process->to_launch = 0;
	}
}

void	core(t_core *core)
{
	static uint8_t	first = 1;
	t_process		*current_process;

	while (core->cycle_to_die > 0)
	{
		core->cycle++;
		core->current_cycle++;
		current_process = core->process;
		while (current_process)
			do_process(core, current_process);
		if (core->current_cycle == core->cycle_to_die)
		{
			core->cycle = 0;
			if (first)
				first = 0;
			else
				cycle_to_die -= CYCLE_DELTA;
		}
	}
}
