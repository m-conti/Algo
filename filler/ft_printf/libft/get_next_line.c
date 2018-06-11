/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 04:40:48 by mconti            #+#    #+#             */
/*   Updated: 2018/05/15 11:56:10 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static char *s[FD_MAX];
	char		buff[BUFF_SIZE + 1];
	int			i;

	i = 0;
	if (fd < 0 || !line || BUFF_SIZE <= 0 || fd > FD_MAX)
		return (-1);
	ft_bzero(buff, BUFF_SIZE + 1);
	while (ft_index(s[fd], '\n') < 0 && (i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (!(s[fd] = ft_strjoinfree(s[fd], buff, OPT1)))
			i = -1;
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	if (!i && s[fd] && !ft_strlen(s[fd]))
		ft_memdel((void**)&s[fd]);
	if (i == -1 || (!i && !s[fd]))
		return (i);
	*line = ft_strcdup(s[fd], '\n');
	if ((i = ft_index(s[fd], '\n')) >= 0)
		s[fd] = ft_strcut(s[fd], i + 1);
	else
		ft_memdel((void**)&s[fd]);
	return (1);
}
