/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:33:32 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/29 11:17:03 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_pars		*ft_get_info(int fd, t_labels **save, t_header **head)
{
	t_pars	*lst;
	char	*line;
	int		counter;

	line = NULL;
	lst = NULL;
	counter = 1;
	while ((get_next_line(fd, &line)) > 0)
	{
		if ((line && *line) || (line && (*head)->magic == 0 && !*line))
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
	if (!lst || (lst && !lst->next && !lst->op_name))
		ft_exit("There aren't any instructions", -1);
	return (lst);
}

t_pars		*ft_parsing(t_pars *lst, t_pars *tmp, t_labels **save)
{
	int		tot_size;

	tot_size = 0;
	while (lst->next)
	{
		if (lst->next && lst->next->position == 0)
		{
			lst->next->position = lst->position + lst->size_code;
			tot_size = lst->position;
		}
		lst = lst->next;
	}
	if (!(lst = ft_get_label(lst->line, lst, save, NULL)))
		ft_exit("get_label failed", lst->line_nb);
	if (!(lst = ft_get_op_name(lst->line, lst)))
		ft_exit("get_op_name failed", lst->line_nb);
	if (!(lst = ft_get_type(lst->line, lst)))
		ft_exit("get_type failed", lst->line_nb);
	if (!(lst = ft_get_size_code(lst)))
		ft_exit("get_size_code failed", lst->line_nb);
	return (tmp);
}

t_pars		*ft_get_code(t_pars *lst, t_labels *label, int fd, int opt)
{
	t_pars	*tmp;
	t_op	op_tab;
	t_pars	*test;

	tmp = lst;
	(label) ? test = label->lst : 0;
	while (lst)
	{
		if (lst->op_code > 0)
		{
			op_tab = g_op_tab[lst->op_code - 1];
			if (!(lst = ft_get_label_values(lst, label, 0, &op_tab)))
				ft_exit("get_label failed", -1);
			if (opt & D)
				if (!(lst = ft_print_hexa(lst)))
					ft_exit("Print hexa out failed", -1);
			if (!(opt & D))
				if (!(lst = ft_get_hexadecimal(lst, fd)))
					ft_exit("get_hexadecimal failed", -1);
		}
		(label) ? label->lst = test : 0;
		lst = lst->next;
	}
	return (tmp);
}

char		*check_line(char *line)
{
	if (!line)
		return (NULL);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!*line)
		return (NULL);
	return (line);
}
