/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:35:35 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/27 14:24:24 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_line(t_core *core, int row)
{
	int i;

	i = 0;
	attron(COLOR_PAIR(COLOR_BORDER));
	mvaddch(2 + row, 0, '*');
	attroff(COLOR_PAIR(COLOR_BORDER));
	while (i < core->v.n_char_row)
	{
		attron(COLOR_PAIR(core->v.colors[(row * core->v.n_char_row) + i]));
		mvprintw(2 + row, 3 + i * 3, "%.2x",
				core->arena[(row * core->v.n_char_row) + i]);
		attroff(COLOR_PAIR(core->v.colors[(row * core->v.n_char_row) + i]));
		mvaddch(2 + row, 3 + i * 3 + 3, ' ');
		i++;
	}
	if (core->v.ncol >= N_CHAR_ROW_MAX * 3 + 4)
	{
		attron(COLOR_PAIR(COLOR_BORDER));
		mvaddch(2 + row, N_CHAR_ROW_MAX * 3 + 4, '*');
		attroff(COLOR_PAIR(COLOR_BORDER));
	}
}

void	print_two_first_lines(t_core *core)
{
	int i;

	i = -1;
	attron(COLOR_PAIR(COLOR_BORDER));
	while (++i < core->v.ncol)
		mvaddch(0, i, '*');
	mvaddch(1, 0, '*');
	if (core->v.ncol >= N_CHAR_ROW_MAX * 3 + 4)
		mvaddch(1, N_CHAR_ROW_MAX * 3 + 4, '*');
	attroff(COLOR_PAIR(COLOR_BORDER));
}

void	print_two_last_lines(t_core *core)
{
	int i;

	if (core->v.nrow >= core->v.n_displayed_lines + 2)
	{
		attron(COLOR_PAIR(COLOR_BORDER));
		mvaddch(core->v.n_displayed_lines + 2, 0, '*');
		if (core->v.ncol >= N_CHAR_ROW_MAX * 3 + 4)
			mvaddch(core->v.n_displayed_lines + 2, N_CHAR_ROW_MAX * 3 + 4, '*');
		i = -1;
		while (++i < core->v.ncol)
			mvaddch(core->v.n_displayed_lines + 3, i, '*');
		attroff(COLOR_PAIR(COLOR_BORDER));
	}
}

void	print_dump(t_core *core)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i && !(i % 64))
			ft_printf("\n");
		if (!(i % 64))
			ft_printf("0x%.4hx : ", i);
		ft_printf("%02hhx ", core->arena[i++]);
	}
	ft_printf("\n");
}
