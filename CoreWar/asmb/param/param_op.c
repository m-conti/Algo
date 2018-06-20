/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:48:35 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/20 14:43:30 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_pars			*ft_get_op_name(char *line, t_pars *lst)
{
	int			i;
	int			l;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (lst);
	else
	{
		l = i;
		while (line[l] && (line[l] != ' ' && line[l] != '\t' && line[l] != '%'))
			l++;
		if (!(lst->op_name = ft_strsub(line, i, l - i)))
			ft_exit("Error malloc", lst->line_nb);
		while (l != i)
			line[--l] = ' ';
		lst->op_code = ft_create_tab(lst->op_name, lst->line_nb);
	}
	return (lst);
}

/*
**what if we have  more then 1 op name? do we check it after in get param?
*/

int				ft_create_tab(char *str, int counter)
{
	static char	**tab_name = NULL;
	int			i;
	char		*s;

	i = 0;
	s = "live ld st add sub and or xor zjmp ldi sti fork lld lldi lfork aff";
	if (counter == -10)
	{
		ft_deltab(tab_name);
		return (0);
	}
	if (!tab_name)
		if (!(tab_name = ft_strsplit(s, ' ')))
			ft_exit("Error malloc in split", counter);
	while (tab_name[i])
	{
		if (ft_strcmp(str, tab_name[i]) == 0)
			return (i + 1);
		i++;
	}
	ft_exit("Wrong operation name", counter);
	return (-1);
}
