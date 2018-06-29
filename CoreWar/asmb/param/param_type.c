/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:48:38 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/29 10:10:38 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_get_value(t_pars **lst, int *tab, int code, char *line)
{
	int		j;
	int		i;
	int		k;

	i = tab[0];
	k = tab[1];
	if (code != 3)
		i++;
	if (!line[i])
		ft_exit("Problem in parsing of param", (*lst)->line_nb);
	j = i;
	(*lst)->type[k] = code;
	while (line[j] && line[j] != ',' && line[j] != ' ' && line[j] != '\t')
		j++;
	if (line[j] == ',' && k == tab[2] - 1)
		ft_exit("Pars problem after last param", (*lst)->line_nb);
	if (!((*lst)->value[k] = ft_strndup(&line[i], j - i)))
		ft_exit("Error malloc", (*lst)->line_nb);
	while (line[j] && line[j] == ' ')
		j++;
	if (line[j] && line[j] == ',')
		j++;
	i = j;
	ft_error_values((*lst)->value[k], code, (*lst)->line_nb);
	return (i);
}

int			type_check(char *line, int i, t_pars **lst, t_op op)
{
	int		j;
	int		tab[3];

	j = 0;
	tab[0] = i;
	tab[1] = 0;
	tab[2] = op.nb_params;
	while (line[tab[0]] && tab[1] < op.nb_params)
	{
		j = 0;
		if (line[tab[0]] == 'r')
			tab[0] = ft_get_value(lst, tab, REG_CODE, line);
		else if (line[tab[0]] == '%')
			tab[0] = ft_get_value(lst, tab, DIR_CODE, line);
		else if ((ft_isdigit(line[tab[0]]) == 1) || (line[tab[0]] == '-'\
		&& line[i + 1] && ft_isdigit(line[i + 1]) == 1) || line[tab[0]] == ':')
			tab[0] = ft_get_value(lst, tab, IND_CODE, line);
		else if (line[tab[0]] && (line[tab[0]] != ' ' && line[tab[0]] != '\t'))
			ft_exit("Error in the params", (*lst)->line_nb);
		while (line[tab[0]] && (line[tab[0]] == ' ' || line[tab[0]] == '\t'))
			tab[0]++;
		tab[1]++;
	}
	return (tab[0]);
}

t_pars		*ft_get_type(char *line, t_pars *lst)
{
	int		i;
	int		k;
	t_op	op_tab;

	k = 0;
	i = 0;
	ft_bzero(&op_tab, sizeof(t_op));
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] && !lst->op_name)
		return (lst);
	else if (!line[i] && lst->op_name)
		ft_exit("Need params", lst->line_nb);
	if (lst->op_code > 0 && lst->op_code <= 16)
		op_tab = g_op_tab[lst->op_code - 1];
	else
		ft_exit("Op_code non valid", lst->line_nb);
	i = type_check(line, i, &lst, op_tab);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		ft_exit("Error after the params", lst->line_nb);
	ft_check_opname_type(lst, lst->op_code, lst->line_nb);
	return (lst);
}
