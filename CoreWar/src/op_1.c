/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:54:11 by mconti            #+#    #+#             */
/*   Updated: 2018/06/16 16:01:59 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op g_op_tab[17];

void	build_array_op(void (*fc_op[17])(t_core*, t_process*))
{
	fc_op[0] = NULL;
	fc_op[1] = &op_live;
	fc_op[2] = &op_ld;
	fc_op[3] = &op_st;
	fc_op[4] = &op_add;
	fc_op[5] = &op_sub;
	fc_op[6] = &op_and;
	fc_op[7] = &op_or;
	fc_op[8] = &op_xor;
	fc_op[9] = &op_zjmp;
	fc_op[10] = &op_ldi;
	fc_op[11] = &op_sti;
	fc_op[12] = &op_fork;
	fc_op[13] = &op_lld;
	fc_op[14] = &op_lldi;
	fc_op[15] = &op_lfork;
	fc_op[16] = &op_aff;
}

void	op_live(t_core *core, t_process *proc)
{
	uint8_t		i;

	i = 0;
	while (i < core->nb_player)
	{
		if (proc->param[0] == core->player[i].nbr)
		{
	//		ft_printf("un processus dit que le joueur \"%s\" est en vie",
	//			core->player[i].header.prog_name);
			show_alive(core->player[i].header.prog_name);
			core->player[i].last_alive = core->cycle;
		}
		proc->lives++;
		core->live++;
		i++;
	}
}

void		op_aff(t_core *core, t_process *proc)
{
	(void)*core;
	(void)*proc;
//	ft_putchar(proc->reg[proc->param[0] - 1] % 256); // sortie AFF
//	MANAGE carry
}

void		do_operator(t_core *core, t_process *proc)
{
	int		i;
	int		dist;
	int		stop;

	dist = 1 + g_op_tab[proc->to_launch - 1].ocp;
	i = 0;
	stop = 0;
	while (i < g_op_tab[proc->to_launch - 1].nb_arg)
	{
		proc->param[i] = read_arena(core, proc, dist, proc->param_len[i]);
		if (proc->param_type[i] == REG_CODE)
			stop |= !in_hex(proc->param[i]);
		dist += proc->param_len[i++];
	}
	if (!stop)
		core->fc_op[proc->to_launch](core, proc);
}