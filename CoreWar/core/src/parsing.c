/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 23:28:53 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/19 23:34:22 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cmp_magic(unsigned char *magic)
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

uint32_t	take_len(char *str)
{
	uint32_t nb;

	nb = str[7] & 0xFF;
	nb |= (str[6] & 0xFF) << 0x8;
	nb |= (str[5] & 0xFF) << 0x10;
	nb |= (str[4] & 0xFF) << 0x18;
	return (nb);
}

int			take_champion(t_core *core, char *file_cor)
{
	int fd;
	int i;

	i = 0;
	while (core->player[i].champ_core && i < 4)
		i++;
	if (core->player[i].champ_core)
		error(TOO_MANY_CHAMP);
	if ((fd = open(file_cor, O_RDONLY)) < 0)
		error(FAIL_OPEN);
	read_champ(fd, &core->player[i]);
	set_player_nbr(core, i);
	return (1);
}

void		read_champ(int fd, t_player *champ)
{
	char buf[2048];

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
	if (!(champ->champ_core = ft_memdup(buf, champ->header.prog_size)))
		error(MALLOC_ERROR);
	if (read(fd, buf, 10) > 0)
		error(SIZEOF_CHAMP);
}

void		make_dump(t_core *core, char *num)
{
	int		i;
	char	*check;

	core->opt_dump = ft_atoll(num);
	i = 0;
	if (!(check = ft_utoa(core->opt_dump)))
		error(MALLOC_ERROR);
	while (num[i] || check[i])
	{
		if (!ft_isdigit(num[i]) || check[i] != num[i])
			error(WRONG_DUMP);
		i++;
	}
	free(check);
	core->opt ^= DUMP;
	core->opt |= ACTIVE_DUMP;
}
