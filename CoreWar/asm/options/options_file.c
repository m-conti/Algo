/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:55:39 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/12 19:22:18 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				check_for_i(int *i)
{
	*i += 1;
	if (*i % 8 == 0)
		ft_printf(" ");
	if (*i >= 16)
	{
		ft_printf("\n");
		*i = 0;
	}
}

void				write_oct_color(unsigned int nb, int size, int *i, char *co)
{
	int				j;
	int				bytes;

	j = 0;
	bytes = size;
	ft_printf(co);
	while (size--)
	{
		bytes--;
		j = nb >> (bytes * 8);
		ft_printf("%02x ", j & 0xFF);
		check_for_i(i);
	}
}

void				ft_print_bonus(t_pars *lst, int k, int bytes, int *i)
{
	unsigned int	tmp;
	t_op			op_tab;
	int				j;

	j = 0;
	op_tab = all_info(lst->op_code - 1);
	while (k < op_tab.nb_params)
	{
		tmp = ft_atoll(lst->value[k]);
		bytes = byte_size(tmp);
		if (lst->type[k] == 1)
			write_oct_color(tmp, 1, i, MAGENTA);
		else if (lst->type[k] == 2 && lst->dir_size == 4)
			write_oct_color(tmp, DIR_SIZE, i, YELLOW);
		else if (lst->type[k] == 3 || lst->type[k] == 2)
			write_oct_color(tmp, IND_SIZE, i, RED);
		k++;
	}
}

t_pars				*ft_print_hexa(t_pars *lst)
{
	int				tmp;
	t_op			op_tab;
	static int		i = 0;

	op_tab = all_info(lst->op_code - 1);
	if (!lst)
		ft_exit("No lst in hexa", 1);
	ft_printf(BOLD);
	write_oct_color(lst->op_code, 1, &i, LCYAN);
	ft_printf(NBOLD);
	tmp = count_op_size(lst);
	if (op_tab.oct_code)
		write_oct_color(tmp, 1, &i, GREEN);
	ft_print_bonus(lst, 0, 0, &i);
	return (lst);
}

void				print_hexa(t_labels *lb, header_t *hd, t_pars *ops, int op)
{
	if (op & I && hd)
		print_header(hd);
	if (ops)
		ft_get_code(ops, lb, 0, op);
	ft_printf("\n\n");
}
