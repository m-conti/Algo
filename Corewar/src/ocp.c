
#include "corewar.h"

extern t_op	g_op_tab[17];

int		calc_param_len(t_process *proc)
{
	int				i;
	int				stop;
	const uint8_t	len[6] = {1, 4, 2, 1, 2, 2};

	stop = 1;
	i = 0;
	if (g_op_tab[proc->to_launch - 1].ocp)
	{
		while (i < g_op_tab[proc->to_launch - 1].nb_arg)
		{
			if (!proc->param_type[i] || !(g_op_tab[proc->to_launch - 1].arg_type[i]
				& (1 << (proc->param_type[i] - 1))))
				stop = 0;
			proc->param_len[i] =
			len[proc->param_type[i] + (3 * g_op_tab[proc->to_launch - 1].mod_direct) - 1];
			i++;
		}
	}
	else
		while (i < g_op_tab[proc->to_launch - 1].nb_arg)
		{
			proc->param_type[i] = g_op_tab[proc->to_launch - 1].arg_type[i] == T_IND ?
			IND_CODE : g_op_tab[proc->to_launch - 1].arg_type[i];
			proc->param_len[i] =
			len[proc->param_type[i] + (3 * g_op_tab[proc->to_launch - 1].mod_direct) - 1];
			i++;
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
	if (proc->to_launch > 0 && proc->to_launch < 16)
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
	ft_printf("jump = %u, len0 = %u, len1 = %u, len2 = %u\n", proc->jump, proc->param_len[0], proc->param_len[1], proc->param_len[2]);
	return (stop);
}