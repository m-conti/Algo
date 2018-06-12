#ifndef OP_STRUCT_H
# define OP_STRUCT_H

# include "ft_printf.h"
# include "op.h"
# include "coredefine.h"
# include <fcntl.h>

typedef	uint32_t	t_reg;
typedef uint16_t	t_index;
typedef uint32_t	t_cycle;

typedef	struct		s_op
{
	char			*name;
	uint8_t			nb_arg;
	t_arg_type		*arg_type;
	uint8_t			op_index;
	t_cycle			cycle_to_launch;
	char			*comment;
	uint8_t			octet_codage_param;
	uint8_t			mod_direct;
}					t_op;

typedef struct		s_player
{
	header_t		header;
	char			*champ_core;
	t_reg			reg[16];
}					t_player;

typedef struct		s_process
{
	int				pc;
	uint8_t			player;
	uint8_t			param_type[3];
	uint8_t			param_len[3];
	uint8_t			process_time;
	uint8_t			to_launch;
	int				jump;
}					t_process;

typedef	struct		s_core
{
	t_process		*process;
	unsigned int	nb_player;
	t_player		player[4];
	uint8_t			arena[MEM_SIZE];
	void			(*fc_op[16])(struct s_core*, t_process*);
	uint32_t		cycle;
	int16_t			current_cycle;
	int16_t			cycle_to_die;
}					t_core;

int print_arena(t_core *core);

#endif
