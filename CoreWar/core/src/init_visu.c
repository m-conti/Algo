/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:59:07 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/27 11:30:17 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_colors_visu(t_core *core)
{
	unsigned int	i;
	uint8_t			cur_col;

	i = 0;
	cur_col = COLOR_PAIR_P1;
	while (i < MEM_SIZE)
	{
		if ((i == core->player[0].header.prog_size) || (core->nb_player >= 2
			&& i == MEM_SIZE / core->nb_player
				+ core->player[1].header.prog_size)
			|| (core->nb_player >= 3 && i == (MEM_SIZE / core->nb_player) * 2
				+ core->player[2].header.prog_size) || (core->nb_player == 4
			&& i == (MEM_SIZE / core->nb_player) * 3
				+ core->player[3].header.prog_size))
			cur_col = 1;
		if (core->nb_player >= 2 && i == MEM_SIZE / core->nb_player)
			cur_col = COLOR_PAIR_P2;
		if (core->nb_player >= 3 && i == (MEM_SIZE / core->nb_player) * 2)
			cur_col = COLOR_PAIR_P3;
		if (core->nb_player == 4 && i == (MEM_SIZE / core->nb_player) * 3)
			cur_col = COLOR_PAIR_P4;
		core->v.colors[i] = cur_col;
		i++;
	}
}

void	init_color_pairs(void)
{
	init_color(COLOR_GRAY, 500, 500, 500);
	init_color(COLOR_LBLUE, 500, 500, 900);
	init_pair(1, COLOR_GRAY, COLOR_BLACK);
	init_pair(COLOR_PAIR_P1, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_PAIR_P2, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_PAIR_P3, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_PAIR_P4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_PROCESS_P1, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_PROCESS_P2, COLOR_BLACK, COLOR_LBLUE);
	init_pair(COLOR_PROCESS_P3, COLOR_BLACK, COLOR_RED);
	init_pair(COLOR_PROCESS_P4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_BORDER, COLOR_GRAY, COLOR_GRAY);
}

void	init_visu(t_core *core)
{
	int offset_col;

	initscr();
	start_color();
	curs_set(0);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	init_color_pairs();
	raw();
	noecho();
	offset_col = 6;
	getmaxyx(stdscr, core->v.nrow, core->v.ncol);
	core->v.n_displayed_lines = (core->v.nrow > N_LINES_MAX) ?
		N_LINES_MAX : core->v.nrow;
	core->v.n_char_row = ((core->v.ncol - offset_col) / 3 > N_CHAR_ROW_MAX)
		? N_CHAR_ROW_MAX : (core->v.ncol - offset_col) / 3;
	init_colors_visu(core);
	core->v.delay = 1000;
	core->v.pause = 0;
	toggle_pause(core);
}

void	print_player(t_player *player, int i)
{
	const int8_t	color[4] = {32, 34, 31, 33};

	ft_printf("Joueur %i :  \" \x1b[%im%s\x1b[0m \"\n\n%s\n\n\n",
		i + 1, color[i], player->header.prog_name, player->header.comment);
}
