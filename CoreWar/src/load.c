/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:51:34 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/11 20:11:49 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_valid_reg(int reg)
{
	return (reg >= 1 && reg <= 16);
}

void	op_ld(t_core *core, t_process *proc)
{
	t_param params;
	uint8_t reg_to_load;
	int     val_to_load;

	//il faudrait utiliser t_op
	read_ocp(core, proc, &params);
	if ((params.param_code_1 >= DIR_CODE) && (params.param_code_2 == REG_CODE))
	{
		reg_to_load = read_arena(core, proc, 2 + params.size_param_1, 1);
		if (is_valid_reg(reg_to_load))
		{
			if (params.param_code_1 == IND_CODE)
				val_to_load = read_arena(core, proc,
						read_arena(core, proc, 2, 2) % IDX_MOD, 4);
			else if (params.param_code_1 == DIR_CODE)
				val_to_load = read_arena(core, proc, 2, 4);
			(core->player[proc->player_num])->reg[reg_to_load] = val_to_load;
			//Manage carry, which goes to 1 if read_arena(core, proc, 2, 2)?? == 0 or val_to_load == 0
			proc->carry = (val_to_load) ? 0 : 1; //not sure
		}
	}
	increase_pc(proc, params.size_param_1 + params.size_param_2);
}

void	op_lld(t_core *core, t_process *proc)
{
	t_param params;
	uint8_t reg_to_load;
	int     val_to_load;

	read_ocp(core, proc, &params);
	if ((params.param_code_1 >= DIR_CODE) && (params.param_code_2 == REG_CODE))
	{
		reg_to_load = read_arena(core, proc, 2 + params.size_param_1, 1);
		if (is_valid_reg(reg_to_load))
		{
			if (params.param_code_1 == IND_CODE)
				val_to_load = read_arena(core, proc,
						read_arena(core, proc, 2, 2), 4);
			else if (params.param_code_1 == DIR_CODE)
				val_to_load = read_arena(core, proc, 2, 4);
			(core->player[proc->player_num])->reg[reg_to_load] = val_to_load;
			proc->carry = (val_to_load) ? 0 : 1; //not sure
		}
	}
	increase_pc(proc, params.size_param_1 + params.size_param_2);
}

void	op_ldi(t_core *core, t_process *proc)
{
	t_param params;

	return ;
}


void	op_lldi(t_core *core, t_process *proc)
{
	t_param params;

	return ;
}
