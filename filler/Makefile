
.PHONY: all re clean fclean

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

NAME	=	mconti.filler 

SRCDIR	=	src

OBJDIR	=	obj

INCDIR	=	include

SRC		=	filler.c		tactic.c		frontier.c		test_frontier.c		mlx.c	\
			init.c			find_player.c	update.c

OBJ		=	$(SRC:.c=.o)

INC		=	filler.h		ft_printf.h		ft_struct.h		get_next_line.h		libft.h	\
			visual.h		images.h

LIBFTPRINTF	=	ft_printf/libftprintf.a

OBJP	=	$(addprefix $(OBJDIR)/, $(OBJ))

INCP	=	$(foreach dir, $(INCDIR), -I$(dir))

MLXFLAG	= -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

all: printfcomp $(OBJDIR) $(NAME)

re: fclean all

printfcomp:
	make all -C ft_printf/

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCP)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	make clean -C ft_printf/
	rm -rf $(OBJDIR)

fclean:
	make fclean -C ft_printf/
	rm -rf $(OBJDIR)
	rm -f $(NAME)

$(NAME): $(OBJP)
	$(CC) $(CFLAGS) -o $@ $^ $(INCP) $(LIBFTPRINTF) $(MLXFLAG)
