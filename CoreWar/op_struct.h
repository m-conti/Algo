#ifndef OP_STRUCT_H
# define OP_STRUCT_H

typedef	uint32_t	t_reg;
typedef uint16_t	t_index;
typedef uint32_t	t_cycle;

typedef	struct		s_op
{
	char			*name;
	uint8_t			nb_arg : 0x3;
	t_arg_type		*arg_type;
	uint8_t			op_index : 0x5;
	t_cycle			cycle_to_launch;
	char			*comment;
	uint8_t			octet_codage_param : 0x1;
	uint8_t			mod_direct : 0x1;
}					t_op;

typedef struct		s_player
{
	header_t		header;
	t_reg			reg[16];
	t_index			*process;
}					t_player;

typedef	struct		s_core
{
	t_player		player[4];
	uint8_t			arena[MEM_SIZE];
}					t_core;

#endif
