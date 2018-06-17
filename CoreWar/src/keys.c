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
