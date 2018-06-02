# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbehra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/02 14:00:49 by tbehra            #+#    #+#              #
#    Updated: 2018/06/02 18:39:13 by tbehra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= lem-in 

SRCDIR	= src
OBJDIR	= obj
INCDIR	= include

SRC		= annexe.c check_status.c lem_in.c road.c room.c 

OBJ		= $(SRC:.c=.o)

LIBFTPRINTF	= ft_printf/libftprintf.a
LIBFT		= ft_printf/libft/libft.a

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
	$(CC) $(CFLAGS) -o $@ $^ $(INCP) $(LIBFTPRINTF) $(LIBFT)
