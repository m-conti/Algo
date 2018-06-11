
#include "op_struct.h"

/*
int		option(char *opt)
{
	const char opt[] = "v"
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

void	place_champion(t_core *core, char *file_cor)
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
}
*/
int		main(int ac, char **av)
{
	t_core	core;

	if (!ac)
		av = NULL;
	ft_bzero((void*)&core, sizeof(t_core));
	ft_printf("%p", core.player);
	return (0);
}