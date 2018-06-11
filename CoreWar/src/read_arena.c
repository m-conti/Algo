/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:36:24 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/11 19:38:08 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	read_ocp(t_core *core, t_process *proc, t_param *res)
{
	const int tab[4] = {0, 1, 4, 2};

	res->ocp = read_arena(core, proc, 1, 1);
	res->param_code_1 = (res->ocp & 0xc0) >> 6;
	res->param_code_2 = (res->ocp & 0x30) >> 4;
	res->param_code_3 = (res->ocp & 0xc) >> 2;
	res->size_param_1 = tab[res->param_code_1];
	res->size_param_2 = tab[res->param_code_2];
	res->size_param_3 = tab[res->param_code_3];
	return (res);
}

void    increase_pc(t_process *proc, int how_much)
{
	(proc->pc += how_much) % MEM_SIZE;
}

int     read_arena(t_core *core, t_process *proc, int offset, int size_to_read)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (i < size_to_read)
	{
		res <<= 8;
		res += core->arena[(proc->pc + offset + i) % MEM_SIZE]
			i++;
	}
	return (res);
}
