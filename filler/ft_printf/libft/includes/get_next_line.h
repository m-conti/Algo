/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 04:40:55 by mconti            #+#    #+#             */
/*   Updated: 2018/05/15 11:56:01 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# define FD_MAX OPEN_MAX
# define BUFF_SIZE 500
# define OPT1 1
# define OPT2 2
# define OPT3 3

int				get_next_line(const int fd, char **line);

#endif
