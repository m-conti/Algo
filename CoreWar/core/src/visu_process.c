/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:37:51 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 22:12:21 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_process_owner(t_core *core, int nb_process, t_process *proc)
{
	mvprintw(Y_NAME, X_NAME, "process no:       %-10i made by: ", nb_process);
	attron(COLOR_PAIR(COLOR_PAIR_P1 + proc->player));
	mvprintw(Y_NAME, X_NAME + 38, "%-20.20s",
		core->player[proc->player].header.prog_name);
	attroff(COLOR_PAIR(COLOR_PAIR_P1 + proc->player));
}

void	print_info_process(t_process *proc)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
		mvprintw(Y_REG + i * 2, X_REG, "Reg[%02i] : %#10x                    ",
			i + 1, proc->reg[i]);
	mvprintw(Y_NAME + 4, X_NAME, "lives of turn:  %3i          carry : %i",
		proc->lives, proc->carry);
}

void	visu_process(t_core *core, int ch)
{
	static int	no_process;
	t_process	*proc;

	if (core->cur_proc == NULL)
	{
		no_process = 1;
		core->cur_proc = core->process;
	}
	proc = core->cur_proc;
	if (proc->to_launch)
		mvprintw(Y_NAME + 8, X_NAME, "current action: \"%s\" to launch : %-28i",
			g_op_tab[proc->to_launch - 1].comment, proc->process_time);
	else
		mvprintw(Y_NAME + 8, X_NAME, "current action: \"move\" to %hu + %-10i",
			proc->pc, proc->jump);
	print_process_owner(core, no_process, proc);
	print_info_process(proc);
	blink_proc(core);
	if (ch == 'n')
	{
		no_process++;
		core->cur_proc = core->cur_proc->next;
	}
}
