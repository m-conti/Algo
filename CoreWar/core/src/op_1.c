/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:54:11 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 22:27:42 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void	print_live(t_core *core, t_process *proc, uint8_t i)
{
	const int8_t	color[4] = {32, 34, 31, 33};
	static uint32_t	len = 0;
	uint8_t			j;

	j = 0;
	if (!len)
		while (j < core->nb_player)
			len = len > ft_strlen(core->player[j++].header.prog_name) ? len :
				ft_strlen(core->player[j - 1].header.prog_name) + 1;
	if (len > 20)
		len = 20;
	ft_printf("\nun processus du joueur \" \x1b[%im%-*s\x1b[0m\" ",
		color[proc->player], len,
		core->player[proc->player].header.prog_name);
	ft_printf("dit que le joueur \" \x1b[%im%-*s\x1b[0m\" est en vie !",
		color[i], len, core->player[i].header.prog_name);
}

void	op_live(t_core *core, t_process *proc)
{
	uint8_t			i;

	i = 0;
	while (i < core->nb_player)
	{
		if (proc->param[0] == core->player[i].nbr)
		{
			if (core->opt & VISU)
				show_alive(core, proc, i);
			else if (core->opt & LIVE)
			{
				print_live(core, proc, i);
				core->opt_num_player = 1;
			}
			core->player[i].last_alive = core->cycle;
		}
		i++;
	}
	proc->lives++;
	core->live++;
}

void	op_aff(t_core *core, t_process *proc)
{
	(void)proc;
	if (core->opt & LIVE)
	{
		if (core->opt_num_player == 1)
		{
			ft_putchar('\n');
			core->opt_num_player = 2;
		}
		ft_putchar(proc->reg[proc->param[0] - 1] % 256);
	}
}

void	do_operator(t_core *core, t_process *proc)
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
