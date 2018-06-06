NAME = libft.a

SRC_PATH = .

OBJ_PATH = .

SRC_NAME =	ft_atoi.c       ft_isprint.c    ft_memmove.c    ft_putstr_fd.c  ft_strequ.c     ft_strncmp.c    ft_strsub.c			\
			ft_bzero.c      ft_isupper.c    ft_memset.c     ft_strcat.c     ft_striter.c    ft_strncpy.c    ft_strtrim.c		\
			ft_countsep.c   ft_itoa.c       ft_putchar.c    ft_strccpy.c    ft_striteri.c   ft_strnequ.c    ft_swap.c			\
			ft_index.c      ft_memalloc.c   ft_putchar_fd.c ft_strchr.c     ft_strjoin.c    ft_strnew.c     ft_tolower.c		\
			ft_isalnum.c    ft_memccpy.c    ft_putendl.c    ft_strclr.c     ft_strlcat.c    ft_strnstr.c    ft_toupper.c		\
			ft_isalpha.c    ft_memchr.c     ft_putendl_fd.c ft_strcmp.c     ft_strlen.c     ft_strrchr.c	ft_abs.c			\
			ft_isascii.c    ft_memcmp.c     ft_putnbr.c     ft_strcpy.c     ft_strmap.c     ft_strrev.c		ft_power.c			\
			ft_isdigit.c    ft_memcpy.c     ft_putnbr_fd.c  ft_strdel.c     ft_strmapi.c    ft_strsplit.c	ft_log.c			\
			ft_islower.c    ft_memdel.c     ft_putstr.c     ft_strdup.c     ft_strncat.c    ft_strstr.c		ft_lstnew.c			\
			ft_memdup.c		ft_lstdelone.c	ft_lstdel.c		ft_lstadd.c		ft_lstradd.c	ft_lstiter.c	ft_lstmap.c			\
			ft_tabdel.c		ft_strndup.c	ft_strcdup.c	ft_strcut.c		ft_error.c		ft_itoabase.c	ft_strjoinfree.c	\
			ft_memindex.c	ft_putcstr.c	ft_strcadd.c	ft_straddc.c	ft_putwchar.c	ft_putwstr.c	ft_wctos.c			\
			ft_wstos.c		ft_wsntos.c		ft_wstrlen.c	get_next_line.c	ft_isvalidnum.c	ft_tablen.c		ft_tabjoin.c		

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CPPFLAGS = -I includes

LDFLAGS = -Llibft

LDLIBS = -lft

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

RM = rm -rf

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC)
	ar -rc $@ $^
	ranlib $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
