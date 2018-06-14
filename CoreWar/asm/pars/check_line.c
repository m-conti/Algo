/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:28:48 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/13 14:41:43 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_pars			*ft_check_line(char *l, t_pars *lst, header_t **hd, int c)
{
	t_pars		*new;

	if ((*hd)->magic == 0)
	{
		if (((ft_hd_name(l, hd, c)) == 1) || ((ft_hd_com(l, hd, c, 0)) == 1))
			return (lst);
		else
		{
			l = ft_comment_delete(l);
			if (!(l = check_line(l)))
				return (lst);
			ft_exit("We need a header", c);
		}
	}
	l = ft_comment_delete(l);
	if (!(l = check_line(l)))
		return (lst);
	if (!(new = ft_init_lst(new, l)))
		ft_exit("Malloc faild(init_lst)", c);
	new->line_nb = c;
	ft_add_lst(&lst, new);
	return (lst);
}

t_pars			*ft_init_lst(t_pars *lst, char *line)
{
	if (!(lst = (t_pars*)malloc(sizeof(t_pars))))
		return (NULL);
	ft_bzero(lst, sizeof(t_pars));
	if (line)
		lst->line = ft_strdup(line);
	return (lst);
}

void			ft_add_lst(t_pars **lst, t_pars *new)
{
	t_pars		*tmp;

	if (new)
	{
		if (*lst)
		{
			tmp = *lst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else if (new)
			*lst = new;
	}
}

void			free_bad_node(t_pars **node, t_pars *lst, t_pars **tmp2)
{
	t_pars		*tmp;

	tmp = *node;
	free(tmp->label);
	tmp->label = NULL;
	free(tmp);
	tmp = lst;
	*tmp2 = lst;
}
