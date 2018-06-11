/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:56:49 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/11 20:11:51 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_st(t_core *core, t_process *proc)
{
	t_param params;
	uint8_t	reg_to_store;
	uint8_t	reg_to_load;

	read_ocp(core, proc, &params);
	if ((params.param_code_1 == REG_CODE) && (params.params_code_2 & 0x1))
	{
		reg_to_store = read_arena(core, proc, 2, 1);
		if (is_valid_reg(reg_to_store))
		{
			if (params.param_code_2 == REG_CODE)
			{
				reg_to_load = read_arena(core, proc, 2, 1);
				if (is_valid_reg(reg_to_load))
					(core->player[proc->player_num])->reg[reg_to_load] = 
							(core->player[proc->player_num])->reg[reg_to_store];
			}
			else if (params.param_code_2 == IND_CODE)
			{
				(core->player[proc->player_num])->reg[reg_to_load] = 
					read_arena(core, proc, read_arena(core, proc, 2, 2) % IDX_MOD, 4);
			}
			//MANAGE CARRY
		}
	}
	increase_proc(proc, params.size_param_1 + params.size_param_2);
}

void	op_st(t_core *core, t_process *proc)
{
	t_param params;
	uint8_t	reg_to_store;
	uint8_t	reg_to_load;

	read_ocp(core, proc, &params);
	if ((params.param_code_1 == REG_CODE) && (params.params_code_2 & 0x1))
	{
		reg_to_store = read_arena(core, proc, 2, 1);
		if (is_valid_reg(reg_to_store))
		{
			if (params.param_code_2 == REG_CODE)
			{
				reg_to_load = read_arena(core, proc, 2, 1);
				if (is_valid_reg(reg_to_load))
					(core->player[proc->player_num])->reg[reg_to_load] = 
							(core->player[proc->player_num])->reg[reg_to_store];
			}
			else if (params.param_code_2 == IND_CODE)
			{
				(core->player[proc->player_num])->reg[reg_to_load] = 
					read_arena(core, proc, read_arena(core, proc, 2, 2), 4);
			}
			//MANAGE CARRY
		}
	}
	increase_proc(proc, params.size_param_1 + params.size_param_2);
}
