/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:58:31 by mconti            #+#    #+#             */
/*   Updated: 2018/06/27 11:27:24 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "ft_printf.h"
# include "op.h"
# include "coredefine.h"
# include "op_struct.h"
# include <fcntl.h>
# include <ncurses.h>

extern const t_op	g_op_tab[17];

int			print_arena(t_core *core);
void		new_process(t_core *core, int pos, int player,
				t_reg reg[REG_NUMBER]);
int			check_op(t_core *core, t_process *proc);
uint32_t	read_arena(t_core *core, t_process *proc, int offset,
				int size_to_read);
void		corewar(t_core *core);
void		init_visu(t_core *core);
void		deal_key(t_core *core, int ch);
t_process	*do_process(t_core *core, t_process *current_process);
void		do_operator(t_core *core, t_process *proc);
void		op_live(t_core *core, t_process *proc);
void		op_ld(t_core *core, t_process *proc);
void		op_ldi(t_core *core, t_process *proc);
void		op_lld(t_core *core, t_process *proc);
void		op_lldi(t_core *core, t_process *proc);
void		op_st(t_core *core, t_process *proc);
void		op_sti(t_core *core, t_process *proc);
void		op_fork(t_core *core, t_process *proc);
void		op_lfork(t_core *core, t_process *proc);
void		op_zjmp(t_core *core, t_process *proc);
void		op_aff(t_core *core, t_process *proc);
void		op_add(t_core *core, t_process *proc);
void		op_sub(t_core *core, t_process *proc);
void		op_and(t_core *core, t_process *proc);
void		op_or(t_core *core, t_process *proc);
void		op_xor(t_core *core, t_process *proc);
void		build_array_op(void (*fc_op[17])(t_core*, t_process*));
void		process_to_die(t_core *core);
void		write_arena(t_core *core, t_process *proc, int offset,
				uint32_t to_write);
uint8_t		in_hex(uint8_t nb);
void		show_alive(t_core *core, t_process *proc, uint8_t i);
void		toggle_pause(t_core *core);
void		init_visu(t_core *core);
void		init_color_pairs(void);
void		init_colors_visu(t_core *core);
int			overflow(int16_t pc, int off_set);
void		set_player_nbr(t_core *core, int i);
void		error(int error);
void		print_two_first_lines(t_core *core);
void		print_two_last_lines(t_core *core);
void		print_line(t_core *core, int row);
void		visu_process(t_core *core, int ch);
void		blink_proc(t_core *core);
int			cmp_magic(unsigned char *magic);
uint32_t	take_len(char *str);
void		read_champ(int fd, t_player *champ);
int			take_champion(t_core *core, char *file_cor);
void		place_champion(t_core *core, t_player *player, int pos);
void		set_player_nbr(t_core *core, int i);
void		make_arena(t_core *core, int nb_player);
void		init_core(t_core *core);
void		take_num_player(t_core *core, char *num);
void		increase_pc(t_process *proc, int how_much);
void		free_all(t_core *core);
t_process	*do_process(t_core *core, t_process *current_process);
void		make_dump(t_core *core, char *num);
void		print_dump(t_core *core);
void		print_player(t_player *player, int i);

#endif
