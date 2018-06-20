# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbehra <tbehra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/02 14:00:49 by tbehra            #+#    #+#              #
#    Updated: 2018/06/20 11:34:51 by tbehra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= ../corewar

SRCDIR	= src
OBJDIR	= obj
LIB_PATH = ../libft/

GREEN = \x1b[32m

WHITE = \x1b[0m

SRCS		=	arena.c	init_visu.c	visu.c	core.c	ocp.c	process.c	\
			op_1.c	op_2.c	op_3.c	op_4.c	keys.c	print_lines.c \
			visu_process.c	main.c	parsing.c	arena_rw.c	op.c \

SRC		= $(addprefix $(SRCDIR)/, $(SRCS))

OBJ		= $(SRC:.c=.o)

INC		=	op.h	op_struct.h		coredefine.h \

INC_PATH = ./includes

LIBFT	= libft.a

OBJP	= $(addprefix $(OBJDIR)/, $(OBJ))
INCP	= $(addprefix $(INC_PATH)/, $(INC))

all: printfcomp $(OBJDIR) $(NAME)

$(NAME): obj $(OBJP)
	@$(CC) $(CFLAGS) -o $@ $(OBJP) -I$(INC_PATH) -I$(LIB_PATH)/includes $(LIBFT) -lncurses
	@echo "${WHITE}corewar			${GREEN}DONE${WHITE}"

printfcomp:
	@make all -C $(LIB_PATH)
	@cp ../libft/libft.a .

obj :
	@mkdir -p obj
	@mkdir -p obj/src

$(OBJDIR)/%.o: %.c $(INCP)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCRULE) -I$(INC_PATH) -I$(LIB_PATH)/includes


clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(OBJDIR) $(LIBFT)

fclean:
	@make fclean -C $(LIB_PATH)
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all
