
.PHONY: all re clean fclean

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= timmy.filler 

SRCDIR	= src
OBJDIR	= obj
INCDIR	= include

SRC		= filler.c 

OBJ		= $(SRC:.c=.o)

LIBFT	= -Llibft/ -lft

OBJP	= $(addprefix $(OBJDIR)/, $(OBJ))
INCP	= $(foreach dir, $(INCDIR), -I$(dir))

all: libftcomp $(OBJDIR) $(NAME)

re: fclean all

libftcomp:
	make all -C libft/

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCP)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	make clean -C libft/
	rm -rf $(OBJDIR)

fclean:
	make fclean -C libft/
	rm -rf $(OBJDIR)
	rm -f $(NAME)

$(NAME): $(OBJP)
	$(CC) $(CFLAGS) -o $@ $^ $(INCP) $(LIBFT)
