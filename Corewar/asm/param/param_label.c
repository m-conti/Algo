/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:48:32 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/13 14:30:59 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**Have to rethink the operation to calculate distance to label
*/

t_pars		*ft_get_label_values(t_pars *l, t_labels *lab, int k, t_op *op_tab)
{
	t_labels	*label;

	label = lab;
	while (k < op_tab->nb_params && (l->type[k] == REG_CODE || l->value[k][0] \
		!= ':'))
	{
		if ((k == op_tab->nb_params - 1) || !l->value[k])
			return (l);
		k++;
	}
	if (k == op_tab->nb_params)
		return (l);
	while (label->next && ft_strequ(&l->value[k][1], label->lst->label) == 0)
		label = label->next;
	(!label) ? ft_exit("Label name not found in label_values", -1) : 0;
	while (label->lst->next && label->lst->op_code == 0)
		label->lst = label->lst->next;
	if (label->lst->position - l->position > 0)
		l->value[k] = ft_itoa((label->lst->position - l->position));
	else
		l->value[k] = ft_itoa(0xFFFF + ((label->lst->position -\
			l->position) + 0x01));
	if (k != op_tab->nb_params)
		l = ft_get_label_values(l, lab, k, op_tab);
	return (l);
}

void		ft_add_label(t_labels **save, t_pars *labeled, int counter)
{
	t_labels *new;
	t_labels *tmp;

	if (!(new = (t_labels*)malloc(sizeof(t_labels))))
		ft_exit("Error malloc t_labels", counter);
	ft_bzero(new, sizeof(t_labels));
	new->lst = labeled;
	if (new)
	{
		if (*save)
		{
			tmp = *save;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else if (new)
			*save = new;
	}
}

/*
**Make sure The *s == ',' does cause problem with real label
*/

t_pars		*ft_get_label(char *line, t_pars *l, t_labels **save)
{
	char	*s;
	int		len;
	int		i;

	if (line && (s = ft_strchr(line, LABEL_CHAR)) != NULL)
	{
		(s != line) ? s-- : s;
		if (*s == DIRECT_CHAR || s == line || *s == ' ' || *s == ',' \
		|| *s == '\t')
			return (l);
		(s != line) ? s++ : s;
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		s[0] = '\0';
		len = ft_strlen(line) - i;
		s[0] = LABEL_CHAR;
		l->label = ft_strsub(line, i, len);
		ft_add_label(save, l, l->line_nb);
		while (line[i] && line[i] != LABEL_CHAR)
			line[i++] = ' ';
		line[i] = ' ';
		ft_check_label(l, i, l->line_nb);
	}
	return (l);
}
