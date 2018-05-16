
.PHONY: all re clean fclean

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= timmy.filler 

SRCDIR	= src
OBJDIR	= obj
INCDIR	= include

SRC		= filler.c tactic.c

OBJ		= $(SRC:.c=.o)

LIBFTPRINTF	= ft_printf/libftprintf.a

OBJP	= $(addprefix $(OBJDIR)/, $(OBJ))
INCP	= $(foreach dir, $(INCDIR), -I$(dir))

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
	$(CC) $(CFLAGS) -o $@ $^ $(INCP) $(LIBFTPRINTF)
