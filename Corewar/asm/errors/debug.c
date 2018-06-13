/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 14:02:22 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/12 00:32:57 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_print_lst(t_pars *lst)
{
	while (lst->next)
		lst = lst->next;
	ft_printf("________________________\n");
	ft_printf(" label : %s\n op_name %s\n op_code %d\n", lst->label,\
	lst->op_name, lst->op_code);
	ft_printf(" op_type[0] %d = %s\n op_type[1] %d = %s\n op_type[2]\
%d = %s\n", lst->type[0], lst->value[0], lst->type[1], lst->value[1],\
	lst->type[2], lst->value[2]);
	ft_printf(" Position = %d\n nb byte = %d\n", lst->position, lst->size_code);
	ft_printf(" label_size = %d\n", lst->label_size);
}

void		ft_print_lst_current(t_pars *lst)
{
	ft_printf("________________________\n");
	ft_printf(" label : %s\n op_name %s\n op_code %d\n", lst->label,\
	lst->op_name, lst->op_code);
	ft_printf(" op_type[0] %d = %s\n op_type[1] %d = %s\n op_type[2]\
%d = %s\n", lst->type[0], lst->value[0], lst->type[1], lst->value[1],\
	lst->type[2], lst->value[2]);
	ft_printf(" Position = %d\n nb byte = %d\n", lst->position, lst->size_code);
	ft_printf(" label_size = %d\n", lst->label_size);
	ft_printf("________________________\n");
}

void		ft_print_labeled(t_labels *lst)
{
	while (lst)
	{
		ft_printf("********************\n");
		ft_printf("%d\n", lst->max_size);
		ft_printf("Label name : %s\n", lst->lst->label);
		ft_printf("%p\n", lst->lst);
		ft_printf("********************\n");
		lst = lst->next;
	}
}
