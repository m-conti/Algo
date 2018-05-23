# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbehra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 13:08:41 by tbehra            #+#    #+#              #
#    Updated: 2018/05/22 13:44:19 by tbehra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= display

SRCDIR	= src
OBJDIR	= obj
INCDIR	= include

SRC		= display.c

OBJ		= $(SRC:.c=.o)

OBJP	= $(addprefix $(OBJDIR)/, $(OBJ))
INCP	= $(foreach dir, $(INCDIR), -I$(dir))
LIBFT	= ../ft_printf/libft/libft.a
LIBFTPRINTF	= ../ft_printf/libftprintf.a

MLXP	= -I/usr/local/include
MLX		= -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

all: $(OBJDIR) $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCP)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean:
	rm -rf $(OBJDIR)
	rm -f $(NAME)

$(NAME): $(OBJP) $(LIBFT) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(INCP) $(MLXP) $(MLX) -I$(LIBFT) -I$(LIBFTPRINTF)
