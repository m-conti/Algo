
#include "op_struct.h"


int		option(char *opt)
{
	const char	all_opt[27] = "abcdefghijklmnopqrstuvwxyz";
	uint		ret;
	int			i;
	uint		test;

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

void	read_champ(int fd, t_player *champ)
{
	int		ret;
	char	buf[2048];

	if (read(fd, buf, 4) < 4)
		error(SIZEOF_COR);
	if (!cmp_magic(buf))
		error(FAKE_MAGIC);
	if (read(fd, buf, 128) < 128)
		error(SIZEOF_COR);
	ft_strcpy(buf, champ->header.prog_name);
	if (read(fd, buf, 8) < 8)
		error(SIZEOF_COR);
	if ((champ->header.prog_size = (uint*)buf[1]) < 1 || (uint*)buf[1] > 682)
		error(SIZEOF_HEAD_PROG_SIZE);
	if (read(fd, buf, 2048) < 2048)
		error(SIZEOF_COR); 
	ft_strcpy(buf, champ->header.prog_comment);
	if (read(fd, buf, champ->header.prog_size)
		< champ->header.prog_size)
		error(SIZEOF_CHAMP);
	champ->champ_core = ft_memdup(buf, champ->header.prog_size);
	if (read(fd, buf, 1) > 0)
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
		error(FAIL_OPEN) ;
	read_champ(fd, core->player[i])
	return (1);
}

void	place_champion(t_core *core, t_player *player, int pos)
{
	int i;

	i = 0;
	while (i < player->header.prog_size)
	{
		core->arena[pos + i] = player->champ_core[i];
		i++;
	}
	ft_memdel((void**)&player->champ_core);
}

void	make_arena(t_core *core, int nb_player)
{
	int		i;

	i = 0;
	while (i < nb_player)
	{
		place_champion(core, &core->player[i], (i * (MEM_SIZE / nb_player)));
		i++;
	}
}

int		main(int ac, char **av)
{
	t_core	core;
	int		i;
	int		opt;
	int		nb_player;

	ft_printf("%i", sizeof(core));
	i = 0;
	nb_player = 0;
	ft_bzero((void*)&core, sizeof(t_core));
	while (++i < ac)
	{
		if (av[i][0] == '-')
			opt |= option(av[i]);
		else
			nb_player += take_champion(&core, av[i]);
	}
	if (!nb_player)
		error(NO_CHAMP);
	make_arena(&core, nb_player);
	return (0);
}