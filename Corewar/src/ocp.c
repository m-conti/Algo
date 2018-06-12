
int		calc_param_len(t_process proc, uint8_t op_nb, uint8_t opt, uint8_t *end)
{
	int				i;
	int				stop;
	const uint8_t	len[6] = {1, 4, 2, 1, 2, 2};

	stop = 1;
	i = 0;
	if (op_nb > 0 && op_nb < 16)
		return (0);
	if (opt)
	{
		while (i < op_tab[op_nb - 1].nb_arg)
		{
			if (!proc->param_type[i] || !(op_tab[op_nb - 1].arg_type[i]
				& (1 << (proc->param_type[i] - 1))))
				stop = 0;
			proc->param_len =
			len[proc->param_type[i] + (3 * op_tab[op_nb - 1].mod_direct) - 1];
		}
	}
	else
		while (i < op_tab[op_nb - 1].nb_arg)
		{
			proc->param_type[i] = op_tab[op_nb - 1].arg_type[i] == T_IND ?
			IND_CODE : op_tab[op_nb - 1].arg_type[i];
			proc->param_len =
			len[proc->param_type[i] + (3 * op_tab[op_nb - 1].mod_direct) - 1];
		}
	return (stop);
}

int		check_op(t_core *core, t_process *proc, uint8_t	op_nb, uint8_t *end)
{
	uint8_t	ocp;
	int		i;
	int		stop;

	ocp = 0;
	ft_bzero(proc->param_type, 3);
	ft_bzero(proc->param_len, 3);
	if (op_nb > 0 && op_nb < 16)
	{
		if (op_tab[op_nb - 1].octet_codage_op_nb)
		{
			i = 3;
			ocp = read_arena(core, proc, 1, 1);
			while (--i)
			{
				ocp >> 2;
				proc->param_type[i] = ocp & 3;
			}
			ocp = 1;
		}
	}
	stop = calc_param_len(proc, op_nb, ocp, end);
	*len = proc->param_len[0] + proc->param_len[1] + proc->param_len[2];
	return (stop);
}