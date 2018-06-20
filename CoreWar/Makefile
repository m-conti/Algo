# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/19 22:24:46 by mmanley           #+#    #+#              #
#    Updated: 2018/06/20 11:50:47 by tbehra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CORE = corewar

ASM = asm

LIBFT = libft

GREEN = \x1b[32m

WHITE = \x1b[0m

CORE_SRCS = arena.c init_visu.c visu.c  core.c  ocp.c   process.c   \
			op_1.c  op_2.c  op_3.c  op_4.c  keys.c  print_lines.c \
			visu_process.c  main.c  parsing.c   arena_rw.c  op.c

ASM_SRCS =	main.c	pars/get_info.c	pars/check_line.c	pars/parsing.c\
			pars/op.c	param/param_op.c	param/param_label.c\
			param/param_code.c	param/param_type.c	errors/errors.c\
		   	errors/debug.c	errors/err_parsing.c	asm_to_byte/create_file.c\
			asm_to_byte/write_bytes.c	options/options.c\
			options/options_file.c	options/options_ft.c

CORE_INCS = op.h	op_struct.h	coredefine.h
ASM_INCS = asm.h	op.h

CORE_DIR = core
ASM_DIR	 = asmb

C_SRC_DIR = $(CORE_DIR)/src
C_INC_DIR = $(CORE_DIR)/includes
CORE_SRC = $(addprefix $(C_SRC_DIR)/, $(CORE_SRCS))
CORE_INC = $(addprefix $(C_INC_DIR)/, $(CORE_INCS))

ASM_INC_DIR = $(ASM_DIR)/includes
ASM_SRC = $(addprefix $(ASM_DIR)/, $(ASM_SRCS))
ASM_INC = $(addprefix $(ASM_INC_DIR)/, $(ASM_INCS))

all : $(CORE) $(ASM) info

$(CORE) : $(CORE_SRC) $(CORE_INC)
	@make -C core

$(ASM) : $(ASM_SRC) $(ASM_INC)
	@make -C asmb

$(LIBFT) :
	@make -C libft

info :
	@echo "${GREEN}DONE${WHITE}"

clean :
	rm -f *.cor
	@make clean -C core
	@make clean -C asmb

fclean : clean
	@make fclean -C core
	@make fclean -C asmb
	@rm -f $(CORE) $(ASM)

re : fclean all

.PHONY: all re clean fclean
