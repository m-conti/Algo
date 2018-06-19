/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 15:01:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/15 17:04:26 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[17];

void	visu_process(t_core *core, char ch)
{
	int			i;
	static int	no_process;
	t_process	*proc;

	if (core->cur_proc == NULL)
	{
		no_process = 1;
		core->cur_proc = core->process;
	}
	i = -1;
	proc = core->cur_proc;
	if (proc->to_launch)
		mvprintw(Y_NAME + 8, X_NAME, "current action: \"%s\" to launch : %-20i", g_op_tab[proc->to_launch - 1].comment, proc->process_time);
	else
		mvprintw(Y_NAME + 8, X_NAME, "current action: \"move\" to %hu + %-20i", proc->pc, proc->jump);
	mvprintw(Y_NAME, X_NAME, "process no:       %-10i made by: ", no_process);
	attron(COLOR_PAIR(COLOR_PAIR_P1 + proc->player));
	mvprintw(Y_NAME, X_NAME + 38, "%-100s", core->player[proc->player].header.prog_name);
	attroff(COLOR_PAIR(COLOR_PAIR_P1 + proc->player));
	while (++i < REG_NUMBER)
		mvprintw(Y_REG + i * 2, X_REG, "Reg[%02i] : %#10x", i + 1, proc->reg[i]);
	mvprintw(Y_NAME + 4, X_NAME, "lives of turn:  %3i          carry : %i", proc->lives, proc->carry);
	if (ch == 'n')
	{
		no_process++;
		core->cur_proc = core->cur_proc->next;
	}
}

void	toggle_pause(t_core *core)
{
	core->v.pause = !(core->v.pause);
	if (core->v.pause)
		mvprintw(Y_PAUSE, X_CYCLE, "Pause");
	else
		mvprintw(Y_PAUSE, X_CYCLE, "     ");
}

void	deal_key(t_core *core, int ch)
{
	visu_process(core, ch);
	if (ch == KEY_END)
	{
		endwin();
		exit (0);
	}
	if (ch == KEY_UP)
	   core->v.delay += 10000;	
	if (ch == KEY_DOWN)
		if (core->v.delay > 10000)
			core->v.delay -= 10000;
	if (ch == ' ')
		toggle_pause(core);
	if (ch == KEY_RIGHT && core->v.pause)
		core->v.pause = -1;
}
