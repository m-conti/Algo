/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:33:35 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/14 16:35:02 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			give_max_size(t_labels **lab, t_pars *lst, header_t **head)
{
	t_labels	*tmp;

	tmp = *lab;
	while (lst->next)
		lst = lst->next;
	(*head)->prog_size = lst->position + lst->size_code;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp->max_size = lst->position + lst->size_code;
		tmp = tmp->next;
	}
}

void			ft_check_path(char *s)
{
	int			i;

	if (!s)
		ft_exit("Bad file or Path", -1);
	i = ft_strlen(s) - 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\t') && i > 0)
		i--;
	if (i - 1 < 0 || s[i] != 's' || s[i - 1] != '.')
		ft_exit("Please check file extension | path", -1);
}

int				main(int ac, char **av)
{
	int			fd;
	t_pars		*op_codes;
	header_t	*head;
	t_labels	*lst_label;
	int			opt;

	lst_label = NULL;
	if (!(head = (header_t*)malloc(sizeof(header_t))))
		return (-1);
	ft_bzero(head, sizeof(header_t));
	if (ac == 1)
		ft_printf("Error\nUsage: ./asm	-[Option -h]	[Path]/[File_name]\n");
	else
	{
		av = option_check(av, ac, &opt);
		ft_check_path(av[0]);
		if ((fd = open(av[0], O_RDONLY)) == -1)
			ft_exit("File doesn't exist", -1);
		op_codes = ft_get_info(fd, &lst_label, &head);
		give_max_size(&lst_label, op_codes, &head);
		op_codes = create_file(av[0], lst_label, head, op_codes);
		(opt & D) ? print_hexa(lst_label, head, op_codes, opt) : 0;
		ft_exit_str(ft_get_filename(av[0]), NULL, GREEN, BOLD);
	}
	return (0);
}
