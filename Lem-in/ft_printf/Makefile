NAME = libftprintf.a

SRC_PATH = .

OBJ_PATH = .

INC_PATH = includes

SRC_NAME =	ft_cast1.c		ft_cast2.c		ft_cast3.c		ft_cast4.c	\
			ft_tr1.c		ft_tr2.c		ft_tr3.c		ft_annexe.c	\
			ft_checkf.c		ft_printf.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

INC_NAME = ft_printf.h		ft_struct.h		libft.h

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

CPPFLAGS = -I $(INC_PATH)

LDFLAGS = -Llibft

LIB = libft/libft.a

LDLIBS = -lft

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

RM = rm -rf

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ) $(INC)
	(cd libft/ ; make all) 	
	-cp $(LIB) ./$(NAME)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC)
	ar -rc $@ $^
	ranlib $@

all: $(NAME)

clean:
	$(RM) $(OBJ)
	(cd libft/ ; make clean)

fclean: clean
	$(RM) $(NAME)
	(cd libft/ ; make fclean)

re: fclean all
