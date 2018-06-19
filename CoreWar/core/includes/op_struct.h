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
	header_t			header;
	uint32_t			nbr;
	char				*champ_core;
	uint32_t			last_alive;
}						t_player;

typedef struct          s_process
{
	int                 pc;
	uint8_t             player;
	uint8_t             lives;
	uint8_t             carry;
	uint8_t             param_type[3];
	uint8_t             param_len[3];
	uint32_t            param[3];
	t_reg               reg[REG_NUMBER];
	uint32_t            process_time;
	uint8_t             to_launch;
	int                 jump;
	struct s_process    *next;
}                       t_process;

typedef struct		s_visu
{
	int				nrow;
	int				ncol;
	unsigned int	nb_process;
	int				n_displayed_lines;
	int				n_char_row;
	uint8_t			colors[MEM_SIZE];
	int				delay;
	int				pause;
}					t_visu;

typedef struct          s_core
{
	t_process           *process;
	t_process			*cur_proc;
	t_visu              v; // V pour visu!
	uint32_t            cycle;
	unsigned int        nb_player;
	unsigned int		nb_process;
	t_player            player[MAX_PLAYERS];
	uint8_t             arena[MEM_SIZE];
	void                (*fc_op[17])(struct s_core*, t_process*);
	int16_t             current_cycle;
	int16_t             cycle_to_die;
	int                 live;
	uint32_t            opt;
	uint32_t			opt_num_player;
	uint8_t				blink;
}                       t_core;

int 	print_arena(t_core *core);
void    new_process(t_core *core, int pos, int player, t_reg reg[REG_NUMBER]);
int		check_op(t_core *core, t_process *proc);
uint32_t	read_arena(t_core *core, t_process *proc, int offset, int size_to_read);
void	corewar(t_core *core);
void		init_visu(t_core *core);
void		deal_key(t_core *core, int ch);

t_process   *do_process(t_core *core, t_process *current_process);
void        do_operator(t_core *core, t_process *proc);
void    op_live(t_core *core, t_process *proc);
void    op_ld(t_core *core, t_process *proc);
void    op_ldi(t_core *core, t_process *proc);
void    op_lld(t_core *core, t_process *proc);
void    op_lldi(t_core *core, t_process *proc);
void    op_st(t_core *core, t_process *proc);
void    op_sti(t_core *core, t_process *proc);
void    op_fork(t_core *core, t_process *proc);
void    op_lfork(t_core *core, t_process *proc);
void    op_zjmp(t_core *core, t_process *proc);
void    op_aff(t_core *core, t_process *proc);
void    op_add(t_core *core, t_process *proc);
void    op_sub(t_core *core, t_process *proc);
void    op_and(t_core *core, t_process *proc);
void    op_or(t_core *core, t_process *proc);
void    op_xor(t_core *core, t_process *proc);
void    build_array_op(void (*fc_op[17])(t_core*, t_process*));
void    process_to_die(t_core *core);
void    write_arena(t_core *core, t_process *proc, int offset, uint32_t to_write);
uint8_t in_hex(uint8_t nb);
void	show_alive(t_core *core, t_process *proc, uint8_t i);
void	toggle_pause(t_core *core);
void	init_visu(t_core *core);
void	init_color_pairs(void);
void	init_colors_visu(t_core *core);
int		overflow(int16_t pc, int off_set);
void	set_player_nbr(t_core *core, int i);
void	error(int error);
void	print_two_first_lines(t_core *core);
void	print_two_last_lines(t_core *core);
void	print_line(t_core *core, int row);
void	visu_process(t_core *core, int ch);
void	blink_proc(t_core *core);

#endif
