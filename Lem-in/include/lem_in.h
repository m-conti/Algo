#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"

# define RESET_COUNT		-1
# define SIZE_LINKS			20	
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

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

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


	int					len_from_start;

	int					route_number; //
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
	void				(*check_status[3])(struct s_anthill*);
	char				*current_line;
	int					nmax_road;
	int					n_roads;
	int					*finished_roads;
}						t_anthill;

typedef struct          s_queue
{
	int                 room;
	t_road              *road;
	struct s_queue      *next;
}                       t_queue;

void					init_anthill(t_anthill *ant);
void					add_line_to_print(t_anthill *ant);
void					parse(t_anthill *ant);
void					path_zero(t_anthill *ant);
void					build_roads(t_anthill *ant);
void					calc_nmax_road(t_anthill *ant);
void					add_to_queue(t_queue *q, int content);
t_queue					*next_element(t_queue *q);
t_queue					*create_queue(int content);
t_queue					*path_room(t_anthill *ant, t_queue *rooms_to_check);
void					add_road(t_anthill *ant, t_road *road);
void					find_road(t_anthill *ant);
void					set_occupied(t_anthill *ant, int room);
t_road					*make_road(t_anthill *ant, int check);
t_road					*new_road(t_anthill *ant, int len_road);
t_queue					*add_queue(int room, t_road *road);
t_queue					*next_queue(t_queue *queue);
t_queue					*trace_roads(t_anthill *ant,
							t_queue *queue, t_road *all_roads);
t_road					*make_road2(t_anthill *ant);
void					init_room(t_room *room, char *name, int x, int y);
void					new_room(t_anthill *ant, char **sp);
void					check_status_nb_ant(t_anthill *ant);
void					check_status_room(t_anthill *ant);
void					check_status_tube(t_anthill *ant);
void					check_command(t_anthill *ant);
char					*get_room_name(char *src);
void					room_copy(t_anthill *ant, t_room *room, int n);
void					reorganize_hill(t_anthill *ant);
int						is_room_name(t_anthill *ant, char *name, int *room);
void					increase_links(t_anthill *ant, int room);
void					add_links(t_anthill *ant, int room1, int room2);
void					error(int err_nb);

void					assign_rooms_to_routes(t_anthill *ant);
int						propagate(t_room *room, t_anthill *ant);
int						can_overwrite(int orig_route, t_room *room, t_anthill *ant);
int						still_a_road(t_room *room, t_anthill *ant, int init_rn);

void					show_rooms(t_anthill *ant);
void					show_roads(t_anthill *ant);

void					add_to_queue(t_queue *q, int content);
t_queue					*next_element(t_queue *q);
t_queue					*create_queue(int content);
t_queue					*path_room(t_anthill *ant, t_queue *rooms_to_check);

void					build_fastest_roads(t_anthill *ant);
int						dijkstra(t_anthill *ant, int road_to_build);
#endif
