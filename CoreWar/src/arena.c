
#include "corewar.h"


void	error(int error)
{
	ft_printf("error : %i\n", error);
	exit(1);
}

int		cmp_magic(unsigned char *magic)
{
	int			i;
	uint32_t	cmp;

	i = 0;
	cmp = 0x18;
	while (i < 4)
	{
		if (magic[i] != ((COREWAR_EXEC_MAGIC >> cmp) & 0xFF))
			return (0);
		cmp -= 8;
		i++;
	}
	return (1);
}

int		option(char *opt)
{
	const char	all_opt[27] = "abcdefghijklmnopqrstuvwxyz";
	uint32_t	ret;
	int			i;
	int			test;

	ret = 0;
	i = 0;
	while (opt[i])
	{
		if ((test = ft_index(all_opt, opt[i++])) < 0)
			error(UNKNOWN_OPT);
		ret |= 1 << test;
	}
	if (ret & ~OUR_OPT)
		error(UNKNOWN_OPT);
	return (ret);
}

uint32_t	take_len(char *str)
{
	uint32_t nb;

	nb = str[7];
	nb += str[6] << 8;
	nb += str[5] << 0x10;
	nb += str[4] << 0x18;
	return (nb);
}

void		read_champ(int fd, t_player *champ)
{
	char		buf[2048];

	if (read(fd, buf, 4) < 4)
		error(SIZEOF_COR);
	if (!cmp_magic((unsigned char*)buf))
		error(FAKE_MAGIC);
	if (read(fd, buf, 128) < 128)
		error(SIZEOF_COR);
	ft_strcpy(champ->header.prog_name, buf);
	if (read(fd, buf, 8) < 8)
		error(SIZEOF_COR);
	champ->header.prog_size = take_len(buf);
	if (!champ->header.prog_size || champ->header.prog_size > CHAMP_MAX_SIZE)
		error(SIZEOF_HEAD_PROG_SIZE);
	if (read(fd, buf, 2048) < 2048)
		error(SIZEOF_COR);
	ft_strcpy(champ->header.comment, buf);
	if (read(fd, buf, 4) < 4)
		error(SIZEOF_COR);
	if (read(fd, buf, champ->header.prog_size) < champ->header.prog_size)
		error(SIZEOF_CHAMP);
	champ->champ_core = ft_memdup(buf, champ->header.prog_size);
	if (read(fd, buf, 10) > 0)
		error(SIZEOF_CHAMP);
}

int		take_champion(t_core *core, char *file_cor)
{
	int		fd;
	int		i;

	i = 0;
	while (core->player[i].champ_core && i < 4)
		i++;
	if (core->player[i].champ_core)
		error(TOO_MANY_CHAMP);
	if ((fd = open(file_cor, O_RDONLY)) < 0)
		error(FAIL_OPEN);
	read_champ(fd, &core->player[i]);
	return (1);
}

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
	if (core->opt & NBRPLAYER)
		;//à faire
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
		set_player_nbr(core, i);
		reg[0] = core->player[i].nbr;
		new_process(core, ((i * MEM_SIZE) / nb_player), i, reg);
		place_champion(core, &core->player[i], ((i * MEM_SIZE) / nb_player));
		i++;
	}
	core->cycle_to_die = CYCLE_TO_DIE;
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
}

int		main(int ac, char **av)
{
	t_core	core;
	int		i;
	int		opt;
	int		nb_player;

	i = 0;
	nb_player = 0;
	opt = 0;
	init_core(&core);
	build_array_op(core.fc_op);
	while (++i < ac)
	{
		if (av[i][0] == '-')
			opt |= option(av[i]);
		else
			nb_player += take_champion(&core, av[i]);
	}
	if (!nb_player)
		error(NO_CHAMP);
	core.nb_player = nb_player;
	make_arena(&core, nb_player);
	init_visu(&core);
	corewar(&core);
	return (0);
}