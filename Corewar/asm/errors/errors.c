/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:35:12 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/14 15:59:03 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_exit(char *message, int i)
{
	if (message && i >= 0)
		ft_printf("%s\nline : [%03d]\n", message, i);
	if (message && i < 0)
		ft_printf("%s\n", message);
	exit(1);
}

void	ft_exit_str(char *name, char *message, char colo[6], char colo2[6])
{
	if (colo)
		ft_printf(colo);
	if (colo2)
		ft_printf(colo2);
	if (name)
		ft_printf("%s was created\n", name);
	else if (message)
		ft_printf("%s\n", message);
	ft_printf(WHITE);
	exit(1);
}
