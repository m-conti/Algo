/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 23:16:15 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/19 23:19:04 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(int error)
{
	ft_printf("error : %i\n", error);
	exit(1);
}

int		option(char *opt)
{
	const char	all_opt[27] = "abcdefghijklmnopqrstuvwxyz";
	uint32_t	ret;
	int			i;
	int			test;

	ret = 0;
	i = 0;
	while (opt[++i])
	{
		if ((test = ft_index(all_opt, opt[i])) < 0)
			error(UNKNOWN_OPT);
		ret |= 1 << test;
	}
	if (ret & ~OUR_OPT)
		error(UNKNOWN_OPT);
	return (ret);
}

int		main(int ac, char **av)
{
	t_core	core;
	int		i;
	int		nb_player;

	i = 0;
	nb_player = 0;
	init_core(&core);
	build_array_op(core.fc_op);
	while (++i < ac)
	{
		if (av[i][0] == '-')
			core.opt |= option(av[i]);
		else if (core.opt & NUMPLAYER)
			take_num_player(&core, av[i]);
		else
			nb_player += take_champion(&core, av[i]);
	}
	if (!nb_player)
		error(NO_CHAMP);
	core.nb_player = nb_player;
	make_arena(&core, nb_player);
	if (core.opt & VISU)
		init_visu(&core);
	corewar(&core);
	return (0);
}
