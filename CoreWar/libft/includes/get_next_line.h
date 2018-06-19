/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfavero <cfavero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 15:50:21 by cfavero           #+#    #+#             */
/*   Updated: 2018/06/19 20:04:43 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# define BUF_SIZE 4
# define ENDL		'\n'

int		get_next_line(const int fd, char **line);
int		get_next_line_mathi(const int fd, char **line);
#endif
