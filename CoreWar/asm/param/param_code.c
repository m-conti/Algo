/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:48:28 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/13 15:09:39 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			count_op_size(t_pars *lst)
{
	int		k;
	int		test;
	int		tmp;

	k = 0;
	tmp = 0;
	test = 6;
	if (!lst)
		return (-1);
	while (k < 3)
	{
		tmp |= lst->type[k] << test;
		k++;
		test -= 2;
	}
	return (tmp);
}

/*
**How to do the overflow in the number of bytes to print
*/

t_pars		*ft_get_hexadecimal(t_pars *lst, int fd)
{
	int		tmp;
	t_op	op_tab;

	op_tab = all_info(lst->op_code - 1);
	if (!lst)
		ft_exit("No lst in hexa", -1);
	write(fd, &lst->op_code, 1);
	tmp = count_op_size(lst);
	if (op_tab.oct_code)
		write(fd, &tmp, 1);
	ft_print_params(lst, fd, 0, 0);
	return (lst);
}

t_pars		*ft_size_count(t_pars *lst, int value, t_op *op_tab)
{
	int k;

	k = -1;
	while (++k < op_tab->nb_params)
	{
		if (lst->type[k] == REG_CODE)
			lst->size_code += 1;
		else if (lst->type[k] == DIR_CODE)
		{
			lst->size_code += value;
			if (lst->value[k][0] == ':')
				lst->label_size = lst->size_code;
		}
		else if (lst->type[k] == IND_CODE)
		{
			lst->size_code += 2;
			if (lst->value[k][0] == ':')
				lst->label_size = lst->size_code;
		}
	}
	return (lst);
}

t_pars		*ft_get_size_code(t_pars *lst, int i, int tot_size)
{
	t_op	op_tab;

	if (lst && lst->op_name)
	{
		lst->size_code = 1;
		op_tab = all_info(lst->op_code - 1);
		lst->size_code += op_tab.oct_code;
		lst = ft_size_count(lst, lst->dir_size, &op_tab);
		if ((lst->position + lst->size_code) > CHAMP_MAX_SIZE)
			ft_exit("File too big", -1);
	}
	return (lst);
}
