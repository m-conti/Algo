#include "filler.h"


#include <fcntl.h> // 
void	ft_log(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	build_piece(t_piece *p, char *line, int log_fd)
{
	char	*pos;
	int		r;

	pos = ft_strchr(line, ' ') + 1;
	if (ft_isdigit(*pos))
		p->nrow = ft_atoi(pos);
		//else ERREUR
	pos = ft_strchr(pos, ' ') + 1;
	if (ft_isdigit(*pos))
		p->ncol = ft_atoi(pos);
	else
		;//ERREUR
	if (!(p->piece = (char**)malloc(sizeof(char*) * p->nrow)))
		return ; //ERREUR
	r = -1;
	while (++r < p->nrow)
	{
		if (!(p->piece[r] = (char*)malloc(sizeof(char) * p->ncol)))
			return ; //ERREUR
		get_next_line(0, &(p->piece[r]));
		ft_log(p->piece[r], log_fd);
	}
}

void	free_piece_tab(t_piece *p)
{
	int i;

	if (p->piece)
	{
		i = 0;
		while (i < p->nrow)
		{
			free(p->piece[i]);
			i++;
		}
	}
	//ft_memdel((void**)p->piece);
}

int main(int ac, char **av)
{
	char		*line;
	int			log_fd; //
	t_piece		p;
	t_filler	f;

	f.ennemy = '^';
	if (!(av))
		return (ac);
	log_fd = open("/Users/tbehra/Documents/projects/Algo_m/filler/log", 
			O_CREAT | O_WRONLY | O_APPEND | O_TRUNC);
	line = ft_strdup("abc");
	while (1)
	{	
		while (ft_strncmp(line, "Piece ", 6) != 0)
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			ft_log(line, log_fd); //
		}
		ft_log("start build piece", log_fd);
		build_piece(&p, line, log_fd);
	//	ft_strdel(&line);
		ft_log("end build piece", log_fd);


		ft_putstr_fd("8 2\n", 1);
		free_piece_tab(&p);
		while (get_next_line(0, &line) == 0)
			;
	}
	//close(log_fd);
	return (0);
}
