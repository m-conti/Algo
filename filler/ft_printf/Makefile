.PHONY: all re clean fclean

CC      = gcc
CFLAGS  = -Wall -Werror -Wextra
NAME	= libftprintf.a

SRCDIR  = src
OBJDIR  = obj
INCDIR	= include

SRC		= parsing.c ft_printf.c tab_conv.c conv_base.c conv_char_str.c		\
		  unicode.c conv_decimal_ints.c padding.c output.c help_conv_str.c

OBJ     = $(SRC:.c=.o)

LIBFT   = -Llibft/ -lft
LIBFTP	= ./libft

OBJP    = $(addprefix $(OBJDIR)/, $(OBJ))
INCP    = $(foreach dir, $(INCDIR), -I$(dir))

all: libftcomp $(OBJDIR) $(NAME)

re: fclean all

libftcomp:
	    make all -C $(LIBFTP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	    $(CC) $(CFLAGS) -c -o $@ $^ $(INCP)

$(OBJDIR):
	    @mkdir -p $(OBJDIR)

clean:
	    make clean -C $(LIBFTP)
		rm -rf $(OBJDIR)

fclean:
	    make fclean -C $(LIBFTP)
		rm -rf $(OBJDIR)
		rm -f $(NAME)

$(NAME): $(OBJP) 
	    ar rc $(NAME) $(OBJP)
