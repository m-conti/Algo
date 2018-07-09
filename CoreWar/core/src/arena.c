/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:46:07 by tbehra            #+#    #+#             */
/*   Updated: 2018/07/09 17:43:40 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	place_champion(t_core *core, t_player *player, int pos)
{
	unsigned int i;

	i = 0;
	while (i < player->header.prog_size)
	{
		core->arena[pos + i] = player->champ_core[i];
		i++;
	}
	ft_memdel((void**)&player->champ_core);
}

void	set_player_nbr(t_core *core, int i)
{
	if (core->opt_num_player)
	{
		core->player[i].nbr = core->opt_num_player;
		core->opt_num_player = 0;
	}
	else
		core->player[i].nbr = ~i;
}

void	make_arena(t_core *core, int nb_player)
{
	int		i;
	t_reg	reg[REG_NUMBER];

	i = 0;
	ft_bzero((void*)reg, REG_SIZE * REG_NUMBER);
	while (i < nb_player)
	{
		reg[0] = core->player[i].nbr;
		new_process(core, ((i * MEM_SIZE) / nb_player), i, reg);
		place_champion(core, &core->player[i], ((i * MEM_SIZE) / nb_player));
		print_player(&core->player[i], i);
		i++;
	}
	core->cycle_to_die = CYCLE_TO_DIE;
	core->opt_num_player = 0;
}

void	init_core(t_core *core)
{
	int i;

	i = 0;
	core->process = NULL;
	ft_bzero((void*)&core->v, sizeof(t_visu));
	core->cycle = 0;
	core->nb_player = 0;
	while (i < MAX_PLAYERS)
		ft_bzero((void*)&core->player[i++], sizeof(t_player));
	ft_bzero((void*)&core->arena, MEM_SIZE);
	core->current_cycle = 0;
	core->cycle_to_die = 0;
	core->live = 0;
	core->opt = 0;
	core->nb_process = 0;
	core->opt_num_player = 0;
	core->blink = 0;
	core->checks = 0;
	core->cur_proc = 0;
}

void	take_num_player(t_core *core, char *num)
{
	int		i;
	char	*check;

	core->opt_num_player = ft_atoll(num);
	i = 0;
	if (!core->opt_num_player)
		error(WRONG_NUM_OF_PLAYER);
	while (core->player[i].champ_core && i < 4)
	{
		if (core->opt_num_player == core->player[i].nbr
				|| !core->opt_num_player)
			error(SAME_NUM_OF_PLAYER);
		i++;
	}
	i = 0;
	if (!(check = ft_utoa(core->opt_num_player)))
		error(MALLOC_ERROR);
	while (num[i] || check[i])
	{
		if (!ft_isdigit(num[i]) || check[i] != num[i])
			error(WRONG_NUM_OF_PLAYER);
		i++;
	}
	free(check);
	core->opt ^= NUMPLAYER;
}
