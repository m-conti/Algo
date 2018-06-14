/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:12:52 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/12 19:15:25 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		**find_non_flag(char **av, int ac)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j] && av[i][j] == ' ')
			j++;
		if (!av[i][j])
			i++;
		else
			break ;
	}
	return (&av[i]);
}

void		print_header(header_t *head)
{
	ft_printf(ORANGE);
	ft_printf("%-12s: ", "Exec_magic");
	ft_printf(LYELLOW);
	ft_printf("-->%#x<--\n", head->magic);
	ft_printf(ORANGE);
	ft_printf("%-12s: ", "Prog_name");
	ft_printf(YELLOW);
	ft_printf("-->%s<--\n", head->prog_name);
	ft_printf(ORANGE);
	ft_printf("%-12s: ", "Prog_size");
	ft_printf(LYELLOW);
	ft_printf("-->%d Bytes<-->%#x<\n", head->prog_size, head->prog_size);
	ft_printf(ORANGE);
	ft_printf("%-12s: ", "Comment");
	ft_printf(YELLOW);
	ft_printf("-->%s<--\n", head->comment);
	ft_printf("\n");
}
