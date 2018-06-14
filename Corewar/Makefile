# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbehra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/02 14:00:49 by tbehra            #+#    #+#              #
#    Updated: 2018/06/14 15:02:44 by tbehra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= corewar

SRCDIR	= src
OBJDIR	= obj
INCDIR	= includes

SRC		= arena.c	visu.c	core.c	ocp.c	process.c	op_1.c

OBJ		= $(SRC:.c=.o)

INC		= op.h		op_struct.h		ft_printf.h	ft_struct.h	get_next_line.h	\
		  libft.h	coredefine.h	op_tab.h

LIBFTPRINTF	= ft_printf/libftprintf.a
LIBFT		= ft_printf/libft/libft.a

OBJP	= $(addprefix $(OBJDIR)/, $(OBJ))
INCP	= $(addprefix $(INCDIR)/, $(INC))
INCRULE	= $(foreach dir, $(INCDIR), -I$(dir))

all: printfcomp $(OBJDIR) $(NAME)

re: fclean all

printfcomp:
	make all -C ft_printf/

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCP)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCRULE)

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
	$(CC) $(CFLAGS) -o $@ $^ $(INCRULE) $(LIBFTPRINTF) $(LIBFT) -lncurses
