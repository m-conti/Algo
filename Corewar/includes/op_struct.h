#ifndef OP_STRUCT_H
# define OP_STRUCT_H

#include "ft_printf.h"
#include "op.h"

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
	uint8_t			player;
	uint8_t			param[3];
}					t_process;

typedef	struct		s_core
{
	t_process		*process;
	t_player		player[4];
	uint8_t			arena[MEM_SIZE];
	void			(*fc_op[16])(struct s_core*, t_process*);
}					t_core;

#endif
