/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:51:59 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/19 22:40:37 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		calc_param_len(t_process *proc)
{
	int				i;
	int				stop;
	const uint8_t	len[6] = {1, 4, 2, 1, 2, 2};

	stop = 1;
	i = -1;
	if (g_op_tab[proc->to_launch - 1].ocp)
		while (++i < g_op_tab[proc->to_launch - 1].nb_arg)
		{
			stop = (!proc->param_type[i] ||
					!(g_op_tab[proc->to_launch - 1].arg_type[i]
					& (1 << (proc->param_type[i] - 1)))) ? 0 : stop;
			if (proc->param_type[i])
				proc->param_len[i] = len[proc->param_type[i]
					+ (3 * g_op_tab[proc->to_launch - 1].mod_direct) - 1];
		}
	else
		while (++i < g_op_tab[proc->to_launch - 1].nb_arg)
		{
			proc->param_type[i] = g_op_tab[proc->to_launch - 1].arg_type[i]
				== T_IND ? IND_CODE : g_op_tab[proc->to_launch - 1].arg_type[i];
			proc->param_len[i] = len[proc->param_type[i]
				+ (3 * g_op_tab[proc->to_launch - 1].mod_direct) - 1];
		}
	return (stop);
}

int		check_op(t_core *core, t_process *proc)
{
	uint8_t	ocp;
	int		i;
	int		stop;

	ft_bzero(proc->param_type, 3);
	ft_bzero(proc->param_len, 3);
	if (proc->to_launch > 0 && proc->to_launch <= 16)
	{
		if (g_op_tab[proc->to_launch - 1].ocp)
		{
			i = 3;
			ocp = read_arena(core, proc, 1, 1);
			while (--i != -1)
			{
				ocp >>= 2;
				proc->param_type[i] = ocp & 3;
			}
		}
	}
	stop = calc_param_len(proc);
	proc->jump = proc->param_len[0] + proc->param_len[1] + proc->param_len[2]
		+ g_op_tab[proc->to_launch - 1].ocp + 1;
	return (stop);
}
