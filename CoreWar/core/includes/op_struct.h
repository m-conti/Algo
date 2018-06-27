/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 00:56:33 by mconti            #+#    #+#             */
/*   Updated: 2018/06/20 11:36:15 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_STRUCT_H
# define OP_STRUCT_H

typedef	uint32_t		t_reg;
typedef uint16_t		t_index;
typedef uint32_t		t_cycle;

typedef	struct			s_op
{
	char				*name;
	uint8_t				nb_arg;
	t_arg_type			arg_type[3];
	uint8_t				op_index;
	t_cycle				cycle_to_launch;
	char				*comment;
	uint8_t				ocp;
	uint8_t				mod_direct;
}						t_op;

typedef struct			s_player
{
	t_header			header;
	uint32_t			nbr;
	char				*champ_core;
	uint32_t			last_alive;
}						t_player;

typedef struct			s_process
{
	int					pc;
	uint8_t				player;
	uint8_t				lives;
	uint8_t				carry;
	uint8_t				param_type[3];
	uint8_t				param_len[3];
	uint32_t			param[3];
	t_reg				reg[REG_NUMBER];
	uint32_t			process_time;
	uint8_t				to_launch;
	int					jump;
	struct s_process	*next;
}						t_process;

typedef struct			s_visu
{
	int					nrow;
	int					ncol;
	unsigned int		nb_process;
	int					n_displayed_lines;
	int					n_char_row;
	uint8_t				colors[MEM_SIZE];
	int					delay;
	int					pause;
}						t_visu;

typedef struct			s_core
{
	t_process			*process;
	t_process			*cur_proc;
	t_visu				v;
	uint32_t			cycle;
	unsigned int		nb_player;
	unsigned int		nb_process;
	t_player			player[MAX_PLAYERS];
	uint8_t				arena[MEM_SIZE];
	void				(*fc_op[17])(struct s_core*, t_process*);
	uint32_t			current_cycle;
	uint32_t			cycle_to_die;
	int					live;
	uint32_t			opt;
	uint32_t			opt_num_player;
	uint32_t			opt_dump;
	uint8_t				blink;
	uint8_t				checks;
}						t_core;

#endif
