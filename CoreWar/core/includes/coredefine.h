/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coredefine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:59:16 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 17:24:10 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREDEFINE_H
# define COREDEFINE_H

# define UNKNOWN_OPT			1
# define SIZEOF_COR				2
# define FAKE_MAGIC				3
# define SIZEOF_HEAD_PROG_SIZE	4
# define SIZEOF_CHAMP			5
# define TOO_MANY_CHAMP			6
# define NO_CHAMP				7
# define FAIL_OPEN				8
# define MALLOC_ERROR			9
# define SAME_NUM_OF_PLAYER		10
# define WRONG_NUM_OF_PLAYER	11
# define WRONG_DUMP				12

/*
** options :
** l = live and comment || v = visual || n = num player
*/

# define OUR_OPT			0x00202800
# define NUMPLAYER			0x00002000
# define VISU				0x00200000
# define LIVE				0x00000800
# define DUMP				0x04000000
# define ACTIVE_DUMP		0x08000000

# define N_CHAR_ROW_MAX		64
# define N_LINES_MAX		64

# define COLOR_GRAY			50
# define COLOR_LBLUE		30
# define COLOR_PAIR_P1		2
# define COLOR_PAIR_P2		3
# define COLOR_PAIR_P3		4
# define COLOR_PAIR_P4		5
# define COLOR_PROCESS_P1	6
# define COLOR_PROCESS_P2	7
# define COLOR_PROCESS_P3	8
# define COLOR_PROCESS_P4	9
# define COLOR_BORDER		10
# define COLOR_BUG			50
# define SLEEP_BLINK		100000

/*
** proc pos
*/

# define X_REG				280
# define Y_REG				34
# define X_NAME				200
# define Y_NAME				34

# define Y_PAUSE			3
# define X_CYCLE			200
# define Y_CYCLE 			5
# define Y_MSG				74
# define X_MSG				140
# define X_DEMARC			196
# define Y_DEMARC			32

# define MIN_COL_DISPLAY	196
# define MIN_ROW_DISPLAY	66

#endif
