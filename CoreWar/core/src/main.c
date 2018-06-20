/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 23:16:15 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/20 11:37:14 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(int error)
{
	const char *error_messages[12] = {"Unknown option",
		"Size of .cor incorrect", "Wrong magic number",
		"Size of header is wrong", "Size of champion is wrong",
		"Too many champions", "No champion", "Fail to open file",
		"Malloc error", "Same number of player", "Wrong number of player",
		"Wrong dumping number"};

	ft_printf("error %i : %s\n", error, error_messages[error - 1]);
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
	if (!ft_strcmp(opt, "-dump"))
		return (DUMP);
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

void	check_arg_number(int ac)
{
	if (ac < 2)
	{
		ft_printf("Usage : corewar champion1.cor champion2.cor (up to 4)\n");
		ft_printf("Options\n");
		ft_printf("\t-v for visualisation\n");
		ft_printf("\t-l to display lives/comments\n");
		ft_printf("\t-n [[player number] [champion.cor]]\n");
		ft_printf("\t-dump [cycle to stop]\n");
		exit(1);
	}
}

void	check_nb_player(int nb_player)
{
	if (!nb_player)
		error(NO_CHAMP);
}

int		main(int ac, char **av)
{
	t_core	core;
	int		i;

	i = 0;
	init_core(&core);
	check_arg_number(ac);
	build_array_op(core.fc_op);
	while (++i < ac)
	{
		if (av[i][0] == '-')
			core.opt |= option(av[i]);
		else if (core.opt & NUMPLAYER)
			take_num_player(&core, av[i]);
		else if (core.opt & DUMP)
			make_dump(&core, av[i]);
		else if (core.nb_player < MAX_PLAYERS)
			core.nb_player += take_champion(&core, av[i]);
		else
			error(TOO_MANY_CHAMP);
	}
	check_nb_player(core.nb_player);
	make_arena(&core, core.nb_player);
	corewar(&core);
	return (0);
}
