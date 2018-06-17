/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:53:45 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/14 14:17:04 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_get_filename(char *name)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	new = NULL;
	while (name && name[i])
		i++;
	i--;
	while (name[i] && (name[i] == ' ' || name[i] == '\t') && i > 0)
		i--;
	if (name[i] != 's' || name[i - 1] != '.')
		ft_exit("Wrong file extension", -1);
	while (name[i] && i > 0 && name[i] != '/')
	{
		i--;
		k++;
	}
	(name[i] == '/') ? k-- : k;
	(name[i] == '/') ? i++ : i;
	new = ft_strsub(name, i, k);
	new = ft_strjoin_free(new, "cor", 1);
	return (new);
}

t_pars		*create_file(char *file, t_labels *lab, header_t *head, t_pars *ops)
{
	char	*cor_file;
	int		fd;

	if (!(cor_file = ft_get_filename(file)))
		ft_exit("Did not get cor file name", 0);
	if ((fd = open(cor_file, O_RDWR | O_CREAT, 0647)) == -1)
		ft_exit("Had a problem with open in creat file", 0);
	write_header(fd, head);
	ops = ft_get_code(ops, lab, fd, 0);
	ft_strdel(&cor_file);
	return (ops);
}
