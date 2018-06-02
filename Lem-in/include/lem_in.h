#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"

# define RESET_COUNT		-1
# define SIZE_LINKS			10 //pour faire chier
# define FREE_FIRST			1
# define FREE_BOTH			3
# define ERROR				0

/*
**			ERROR
*/
# define GNL_ERROR			0
# define EMPTY_LINE			1
# define WRONG_ANT_NUMBER	2
# define MULTIPLE_START		3
# define MULTIPLE_END		4
# define SAME_ROOM_NAME		5
# define SAME_ROOM_POSITION	6
# define MALLOC_ERROR		7
# define INVALID_ROOM		8
# define NO_ESCAPE			9
# define ROOM_NOT_FOUND		404 // retiré
# define HELL_ROOM			666
# define FREEDOM			1984
# define FATAL_ERROR		2000 // retiré

/*
**		PARSE_STATUS
*/
# define NB_ANT_CHECK		0
# define ROOM_CHECK			1
# define TUBE_CHECK			2

typedef struct			s_room
{
	char				*name;
	struct s_room		*next;
	int					*links;
	int					nb_links;
	int					x;
	int					y;
	uint8_t				type; //seems useless
	uint16_t			occupied;
}						t_room;

typedef	struct			s_road
{
	int					*rooms;
	int					len;
	int					check;
	struct s_road		*next;
}						t_road;

typedef struct			s_path
{
	int					*distance;
	int					*prev_room;
}						t_path;

typedef struct			s_anthill
{
	uint8_t				stop;
	t_room				*hill;
	int					nb_ant;
	int					nb_room;
	int					start;
	int					end;
	char				*lines;
	t_path				path;
	t_road				*road;
	int					parstatus;
	void				check_status[3](struct s_anthill*, char*);
	char				*current_line;
	int					nmax_road;
}						t_anthill;

typedef struct 			s_queue;
{
	int					d;
	struct s_queue		*next;
}						t_queue;

#endif