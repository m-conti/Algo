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

void	visu_process(t_core *core, t_process *proc, int no_process)
{
	int		i;

	i = -1;
	mvprintw(Y_NAME, X_NAME, "process no: %-10i made by: %-100s", no_process,core->player[proc->player].header.prog_name);
	while (++i < REG_NUMBER)
		mvprintw(Y_REG + i * 2, X_REG, "Reg[%02i] : %#10x", i + 1, proc->reg[i]);
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
	static t_process	*proc = NULL;
	static int			no_process;

	if (!proc)
	{
		no_process = 1;
		proc = core->process;
	}
	visu_process(core, proc, no_process);
	if (ch == 'n')
	{
		no_process++;
		proc = proc->next;
	}
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
