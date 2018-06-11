/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:13:21 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/11 19:57:41 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

typedef struct		s_param
{
	//surement a mettre dans t_core
	uint8_t			ocp;
	uint8_t			param_code_1;
	uint8_t			param_code_2;
	uint8_t			param_code_3;
	uint8_t			size_param_1;
	uint8_t			size_param_2;
	uint8_t			size_param_3;
}					t_param;

void	op_live(t_core *core, t_process *proc)
{
	int	player;
	
	player = read_arena(core, proc, 0, 4);
	//add live, display if player exists
	//start_counter_cycle(20);
	increase_pc(proc, 4);
}

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
