/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 15:01:30 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/19 22:12:19 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	blink_proc(t_core *core)
{
	int			blink_status;
	t_process	*cur;
	int			color;

	cur = core->cur_proc;
	blink_status = 0;
	if (core->blink && core->v.pause && core->v.ncol >= MIN_COL_DISPLAY
		&& core->v.nrow >= MIN_ROW_DISPLAY)
	{
		while (blink_status < 2)
		{
			color = (blink_status % 2) ?
				COLOR_PROCESS_P1 + cur->player : core->v.colors[cur->pc];
			attron(COLOR_PAIR(color));
			mvprintw(2 + (cur->pc / core->v.n_char_row), 3 +
				(cur->pc % core->v.n_char_row) * 3, "%.2x",
				core->arena[cur->pc]);
			blink_status++;
			refresh();
			usleep(SLEEP_BLINK);
			attroff(COLOR_PAIR(color));
		}
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
		exit(0);
	}
	if (ch == 'b')
		core->blink = !core->blink;
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
