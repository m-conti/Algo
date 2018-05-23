/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:16:31 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/22 16:56:32 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	display_frontier(t_filler *f)
{
	int i;
	int j;
	
	i = 0;
	while (i < f->ymax)
	{
		j = 0;
		while (j < f->xmax)
		{
			if (f->frontier[i][j] == -1)
				ft_putchar_fd('2', f->fd);
			else if (f->frontier[i][j] == 0)
				ft_putchar_fd('0', f->fd);
			else
				ft_putchar_fd('1', f->fd);
			j++;
		}
		i++;
		ft_putchar_fd('\n', f->fd);
	}
		ft_putchar_fd('\n', f->fd);
}

void	parse_tab_display(t_filler *f)
{
	int i;
	
	i = 0;
	while (i < f->ymax)
	{
		ft_putstr_fd(f->tab[i], f->fd);
		ft_putchar_fd('\n', f->fd);
		i++;
	}
	ft_putchar_fd('\n', f->fd);
}

void	parse_first_time_display(t_filler *f)
{
	ft_putchar_fd(f->player, f->fd);
	ft_putchar_fd('\n', f->fd);
	ft_putnbr_fd(f->ymax, f->fd);
	ft_putchar_fd('\n', f->fd);
	ft_putnbr_fd(f->xmax, f->fd);
	ft_putchar_fd('\n', f->fd);
}
