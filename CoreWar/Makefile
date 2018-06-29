# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/19 22:24:46 by mmanley           #+#    #+#              #
#    Updated: 2018/06/29 13:07:41 by mmanley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CORE = corewar

ASM = asm

LIBFT = libft/libft.a

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

LFT_SRCS = ft_isalnum.c ft_memccpy.c ft_putchar.c ft_putstr_fd.c ft_strdup.c \
		   ft_strmap.c ft_strnstr.c ft_toupper.c ft_isalpha.c ft_memchr.c \
		   ft_putchar_fd.c ft_strcat.c ft_strequ.c ft_strmapi.c ft_strrchr.c \
		   ft_isascii.c ft_memcmp.c ft_putendl.c ft_strchr.c ft_striter.c \
		   ft_strncat.c ft_strsplit.c ft_isdigit.c ft_memcpy.c ft_putendl_fd.c \
		   ft_strclr.c ft_striteri.c ft_strncmp.c ft_strstr.c ft_isprint.c \
		   ft_memdel.c ft_putnbr.c ft_strcmp.c ft_strjoin.c ft_strncpy.c \
		   ft_strsub.c ft_atoi.c ft_itoa.c ft_memmove.c ft_putnbr_fd.c \
		   ft_strcpy.c ft_strlcat.c ft_strnequ.c ft_strtrim.c ft_bzero.c \
		   ft_memalloc.c ft_memset.c ft_putstr.c ft_strdel.c ft_strlen.c \
		   ft_strnew.c ft_tolower.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
		   ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_sqrt.c ft_is_prime.c \
		   ft_find_next_prime.c ft_swap.c ft_div_mod.c ft_atoll.c get_next_line.c\
		   get_next_line_mathi.c ft_strjoin_free.c ft_strndup.c ft_occ_pos.c\
		   ft_deltab.c ft_tablen.c rec_nbr_count.c ft_print_bits.c ft_index.c\
		   ft_memdup.c ft_utoa.c

CORE_INCS = op.h	op_struct.h	coredefine.h
ASM_INCS = asm.h	op.h
LFT_INCS = ft_printf.h	ft_struct.h	get_next_line.h	libft.h

CORE_DIR = core
ASM_DIR = asmb
LFT_DIR = libft

C_SRC_DIR = $(CORE_DIR)/src
C_INC_DIR = $(CORE_DIR)/includes
CORE_SRC = $(addprefix $(C_SRC_DIR)/, $(CORE_SRCS))
CORE_INC = $(addprefix $(C_INC_DIR)/, $(CORE_INCS))

ASM_INC_DIR = $(ASM_DIR)/includes
ASM_SRC = $(addprefix $(ASM_DIR)/, $(ASM_SRCS))
ASM_INC = $(addprefix $(ASM_INC_DIR)/, $(ASM_INCS))

LFT_INC_DIR = $(LFT_DIR)/includes
LFT_SRC = $(addprefix $(LFT_DIR)/, $(LFT_SRCS))
LFT_INC = $(addprefix $(LFT_INC_DIR)/, $(LFT_INCS))

all : complibft compcore compasm info

complibft:
	@make -C libft

compcore:
	@make -C core

compasm:
	@make -C asmb

debug:
	@make debug -C asmb
	@make debug -C core

info :
	@echo "${GREEN}DONE${WHITE}"

corclean:
	@rm -f *.cor

clean :
	@make clean -C core
	@make clean -C asmb
	@make clean -C libft

fclean : clean
	@make fclean -C core
	@make fclean -C asmb
	@make fclean -C libft
	@rm -f $(CORE) $(ASM)

re : fclean all

.PHONY: all re clean fclean
