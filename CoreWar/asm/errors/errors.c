/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:35:12 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/19 13:55:43 by mmanley          ###   ########.fr       */
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

int		isal_lbch(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	if (s[i] == c)
		return (1);
	else
		return (-1);
}
