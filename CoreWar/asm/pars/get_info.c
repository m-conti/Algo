/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:33:32 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/13 15:00:41 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**If label By it's self no lst_add
*/

t_pars		*ft_get_info(int fd, t_labels **save, header_t **head)
{
	t_pars	*lst;
	char	*line;
	int		counter;

	line = NULL;
	counter = 1;
	while ((get_next_line(fd, &line)) > 0)
	{
		if (line && *line)
		{
			lst = ft_check_line(line, lst, head, counter);
			if (lst && check_line(line))
			{
				if (!(lst = ft_parsing(lst, lst, save)))
					ft_exit("Ft_parsing failed", counter);
			}
		}
		counter++;
		ft_strdel(&line);
	}
	return (lst);
}

t_pars		*ft_parsing(t_pars *lst, t_pars *tmp, t_labels **save)
{
	int		tot_size;

	tot_size = 0;
	while (lst->next)
	{
		if (lst->next)
		{
			lst->next->position = lst->position + lst->size_code;
			tot_size = lst->position;
		}
		lst = lst->next;
	}
	if (!(lst = ft_get_label(lst->line, lst, save)))
		ft_exit("get_label failed", lst->line_nb);
	if (!(lst = ft_get_op_name(lst->line, lst)))
		ft_exit("get_op_name failed", lst->line_nb);
	if (!(lst = ft_get_type(lst->line, lst)))
		ft_exit("get_type failed", lst->line_nb);
	if (!(lst = ft_get_size_code(lst, lst->op_code, tot_size)))
		ft_exit("get_size_code failed", lst->line_nb);
	return (tmp);
}

t_pars		*ft_get_code(t_pars *lst, t_labels *label, int fd, int opt)
{
	t_pars	*tmp;
	t_op	op_tab;

	tmp = lst;
	while (lst)
	{
		if (lst->op_code > 0)
		{
			op_tab = all_info(lst->op_code - 1);
			if (!(lst = ft_get_label_values(lst, label, 0, &op_tab)))
				ft_exit("get_label failed", -1);
			if (opt & D)
			{
				if (!(lst = ft_print_hexa(lst)))
					ft_exit("Print hexa out failed", -1);
			}
			else
			{
				if (!(lst = ft_get_hexadecimal(lst, fd)))
					ft_exit("get_hexadecimal failed", -1);
			}
		}
		lst = lst->next;
	}
	return (tmp);
}

char		*check_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!line || !*line)
		return (NULL);
	return (line);
}

t_op		all_info(int i)
{
	static t_op	op_tab[17] = {
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0}, {"ld", 2, {T_DIR
		| T_IND, T_REG}, 2, 5, "load", 1, 0}, {"st", 2, {T_REG, T_IND | T_REG},
		3, 5, "store", 1, 0}, {"add", 3, {T_REG, T_REG, T_REG}, 4, 10,
		"addition", 1, 0}, {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10,
		"soustraction", 1, 0}, {"and", 3, {T_REG | T_DIR | T_IND, T_REG |
		T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
			"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
			"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
			"store index", 1, 1}, {"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1}, {"lfork", 1, {T_DIR}, 15, 1000, "long fork",
		0, 1}, {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
		{0, 0, {0}, 0, 0, 0, 0, 0}};

	return (op_tab[i]);
}
