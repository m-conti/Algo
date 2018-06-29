# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/05 11:40:02 by mmanley           #+#    #+#              #
#    Updated: 2018/06/29 11:27:49 by mmanley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../asm

DEBUG = ../debug_asm

FLGS = -Wall -Wextra -Werror

LIB = libft.a

LIBP = ../libft

INC = includes

LIBI = ../libft/includes

RED = \x1b[31m

GREEN = \x1b[32m

WHITE = \x1b[0m

OBJ_PATH = objs/

FAN = -fsanitize=address,undefined -g

SRCS =	main.c\
		pars/get_info.c\
		pars/check_line.c\
		pars/parsing.c\
		pars/op.c\
		param/param_op.c\
		param/param_label.c\
		param/param_code.c\
		param/param_type.c\
		errors/errors.c\
		errors/debug.c\
		errors/err_parsing.c\
		asm_to_byte/create_file.c\
		asm_to_byte/write_bytes.c\
		options/options.c\
		options/options_file.c\
		options/options_ft.c\

OBJS_BASE = $(SRCS:%.c=%.o)

OBJS = $(addprefix $(OBJ_PATH), $(OBJS_BASE))

all : comp_lib $(NAME)
	@echo > /dev/null

$(NAME) : objs $(OBJS)
	@gcc -o $@ $(OBJS) $(LIBP)/$(LIB) -I $(LIBI)/ -I ./$(INC)
	@echo "${WHITE}Asm			${GREEN}DONE${WHITE}"

debug : comp_lib objs $(OBJS)
	@gcc -o $(DEBUG) $(OBJS) $(LIBP)/$(LIB) -I $(LIBI)/ -I ./$(INC) $(FAN)
	@echo "${WHITE}Asm debug version	${GREEN}DONE${WHITE}"

comp_lib:
	@make -C $(LIBP)

objs :
	@mkdir -p objs/errors
	@mkdir -p objs/pars
	@mkdir -p objs/param
	@mkdir -p objs/options
	@mkdir -p objs/asm_to_byte

$(OBJ_PATH)%.o: %.c $(INC)/asm.h $(INC)/op.h $(LIBP)/$(LIB)
	@gcc -o $@ -c $< -I $(LIBI)/ -I ./$(INC)  $(FLGS)

clean :
	@rm -rf $(OBJS) objs
	@make clean -C $(LIBP)

fclean : clean
	@make fclean -C $(LIBP)
	@rm -f $(NAME) $(DEBUG)

re : fclean all
