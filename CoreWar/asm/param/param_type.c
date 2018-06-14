/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:48:38 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/13 13:38:21 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_get_value(t_pars **lst, int k, int i, int code, char *line)
{
	int j;

	if (code != 3)
		i++;
	j = i;
	(*lst)->type[k] = code;
	while (line[j] && line[j] != ',' && line[j] != ' ')
		j++;
	(*lst)->value[k] = ft_strndup(&line[i], j - i);
	while (line[j] && line[j] == ' ')
		j++;
	if (line[j] && line[j] == ',')
		j++;
	i = j;
	ft_error_values((*lst)->value[k], code, (*lst)->line_nb);
	return (i);
}

/*
** check if ft_strdup return NULL
*/

t_pars		*ft_get_type(char *line, t_pars *lst)
{
	int i;
	int k;
	int j;

	k = 0;
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] && !lst->op_name)
		return (lst);
	else if (!line[i] && lst->op_name)
		ft_exit("Need params", lst->line_nb);
	while (line[i] && k < 3)
	{
		j = 0;
		if (line[i] == 'r')
			i = ft_get_value(&lst, k, i, REG_CODE, line);
		else if (line[i] == '%')
			i = ft_get_value(&lst, k, i, DIR_CODE, line);
		else if ((ft_isdigit(line[i]) == 1) || (line[i] == '-' && line[i + 1]\
		&& ft_isdigit(line[i + 1]) == 1) || line[i] == ':')
			i = ft_get_value(&lst, k, i, IND_CODE, line);
		else if (line[i] && (line[i] != ' ' && line[i] != '\t'))
			ft_exit("Error in the params", lst->line_nb);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		k++;
	}
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		ft_exit("Error after the params", lst->line_nb);
	ft_check_opname_type(lst, lst->op_code, lst->line_nb);
	return (lst);
}
