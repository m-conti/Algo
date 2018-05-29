#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"

# define RESET_COUNT		-1

/*
**			ERROR
*/
# define GNL_ERROR			0
# define EMPTY_LINE			1
# define WRONG_ANT_NUMBER	2
# define MULTIPLE_START		3
# define MULTIPLE_END		4
# define SAME_ROOM_NAME		5
# define HELL_ROOM			666

/*
**		PARSE_STATUS
*/
# define NB_ANT_CHECK		0
# define ROOM_CHECK			1
# define TUBE_CHECK			2

typedef struct			s_room
{
	char				*name;
	s_room				*next;
	int					*links;
	int					nb_links;
	uint8_t				type;
	uint8_t				ant;
}						t_room;

typedef struct			s_strings
{
	char				*str;
	struct s_strings	*next;
}						t_strings;

typedef struct			s_anthill
{
	t_room				*hill;
	int					nb_ant;
	int					nb_room;
	int					start;
	int					end;
	t_strings			*lines;
	int					parstatus;
	void				check_status[3](struct s_anthill*, char*);
	char				*current_line;
}						t_anthill;

#endif