NAME = libftprintf.a

SRC_PATH = .

OBJ_PATH = .

INC_PATH = ../includes

LIB_PATH = ../

GREEN = \x1b[32m

WHITE = \x1b[0m

SRC_NAME =	ft_cast1.c		ft_cast2.c		ft_cast3.c		ft_cast4.c	\
			ft_tr1.c		ft_tr2.c		ft_tr3.c		ft_annexe.c	\
			ft_checkf.c		ft_printf.c		ft_wctos.c		ft_wstos.c	\
			ft_log.c		ft_memindex.c	ft_isupper.c	ft_abs.c	\

OBJ_NAME =	$(SRC_NAME:.c=.o)

INC_NAME = ft_printf.h		ft_struct.h

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

all: $(NAME)
	@echo > /dev/null

$(NAME): $(OBJ) $(INC)
	@ar -rc $@ $^
	@ranlib $@
	@echo "libftprintf.a${GREEN}		DONE${WHITE}"

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $< -I$(INC_PATH)/ -I$(LIB_PATH)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
