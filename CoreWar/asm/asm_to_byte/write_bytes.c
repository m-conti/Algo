/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:21:15 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/13 20:22:47 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				write_oct(int fd, unsigned int nbr, int code_size)
{
	int				j;
	int				bytes;

	j = 0;
	bytes = code_size;
	while (code_size--)
	{
		bytes--;
		j = nbr >> (bytes * 8);
		write(fd, &j, 1);
	}
}

int					byte_size(unsigned int w)
{
	int				bsize;

	bsize = 0;
	if (w <= 0xFF)
		bsize = 1;
	else if (w > 0xFF && w <= 0xFFFF)
		bsize = 2;
	else if (w > 0xFFFF && w <= 0xFFFFFF)
		bsize = 3;
	else if (w > 0xFFFFFF && w <= 0xFFFFFFFF)
		bsize = 4;
	return (bsize);
}

void				ft_print_params(t_pars *lst, int fd, int k, int bytes)
{
	unsigned int	tmp;
	t_op			op_tab;
	int				j;

	j = 0;
	op_tab = all_info(lst->op_code - 1);
	while (k < op_tab.nb_params)
	{
		tmp = ft_atoll(lst->value[k]);
		bytes = byte_size(tmp);
		if (lst->type[k] == 1)
			write(fd, &tmp, 1);
		else if (lst->type[k] == 2 && lst->dir_size == 4)
			write_oct(fd, tmp, DIR_SIZE);
		else if (lst->type[k] == 3 || lst->type[k] == 2)
			write_oct(fd, tmp, IND_SIZE);
		k++;
	}
}

void				ft_write_bits(unsigned char octet, int size, int fd)
{
	int				oct;

	oct = octet;
	if (size)
	{
		ft_write_bits(octet >> 1, size - 1, fd);
		ft_putchar_fd((oct & 1), fd);
	}
}

void				write_header(int fd, header_t *head)
{
	int				len;
	int				bytes;
	int				j;

	bytes = byte_size(head->magic);
	write_oct(fd, head->magic, DIR_SIZE);
	len = ft_strlen(head->prog_name);
	write(fd, head->prog_name, len);
	ft_write_bits(0, PROG_NAME_LENGTH - len, fd);
	j = 0;
	write(fd, &j, 4);
	write_oct(fd, head->prog_size, 4);
	len = ft_strlen(head->comment);
	write(fd, head->comment, len);
	ft_write_bits(0, COMMENT_LENGTH - len, fd);
	j = 0;
	write(fd, &j, 4);
}
