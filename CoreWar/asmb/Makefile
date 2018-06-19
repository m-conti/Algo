# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/05 11:40:02 by mmanley           #+#    #+#              #
#    Updated: 2018/06/19 22:46:56 by mmanley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

CFLAGS = -Wall -Wextra -Werror

LIB = libft.a

LIB_PATH = ../libft

INC = includes

LIB_INC = ../libft/includes

RED = \x1b[31m

GREEN = \x1b[32m

WHITE = \x1b[0m

OBJ_PATH = objs/

FAN = -fsanitize=address -g3

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

all : $(LIB) $(NAME)

$(NAME) : objs $(OBJS)
	@gcc -o $@ $(OBJS) $(LIB_PATH)/$(LIB) -I $(LIB_INC)/ -I ./$(INC) $(CFLAGS)
	@cp $(NAME) ../
	@echo "${WHITE}Asm			${GREEN}DONE${WHITE}"

$(LIB) :
	@make -C $(LIB_PATH)

objs :
	@mkdir -p objs
	@mkdir -p objs/errors
	@mkdir -p objs/pars
	@mkdir -p objs/param
	@mkdir -p objs/options
	@mkdir -p objs/asm_to_byte

$(OBJ_PATH)%.o: %.c $(INC)/asm.h $(INC)/op.h
	@gcc -o $@ -c $< -I $(LIB_INC)/ -I ./$(INC)

Champs:
	./asm  ../vm_champs/champs/championships/2017/iburel/gateau.s -di
	./asm  ../vm_champs/champs/championships/2017/pzarmehr/overwatch.s  -di
	./asm  ../vm_champs/champs/championships/2017/tbillard/Douceur_power.s -di
	./asm  ../vm_champs/champs/championships/2017/jaustry/mise_a_jour_windows95.s -di
	./asm  ../vm_champs/champs/championships/2017/adenis/Explosive_Kitty.s -di
	./asm  ../vm_champs/champs/championships/2017/agregoir/Kittystrophic.s -di
	./asm  ../vm_champs/champs/championships/2017/gnebie/ultima.s -di
	./asm  ../vm_champs/champs/championships/2017/nolivier/run_Kitty_RUN.s -di
	./asm test1.s -di
	./asm  ../vm_champs/champs/championships/2014/brandazz/Rainbow_dash.s -di
	./asm  ../vm_champs/champs/championships/2014/bguy/sam_2.0.s -di
	./asm  ../vm_champs/champs/championships/2014/bjacob/doge.s -di
	./asm  ../vm_champs/champs/championships/2014/cdivry/youforkmytralala.s -di
	./asm  ../vm_champs/champs/championships/2014/clafleur/big_feet.s -di
	./asm  ../vm_champs/champs/championships/2014/dcohen/loose.s -di
	./asm  ../vm_champs/champs/championships/2014/ekocevar/mandragore.s -di
	./asm  ../vm_champs/champs/championships/2014/esusseli/gedeon.s -di
	./asm  ../vm_champs/champs/championships/2014/evlasova/terminator.s -di
	./asm  ../vm_champs/champs/championships/2014/fcorre/ultimate-surrender.s -di
	./asm  ../vm_champs/champs/championships/2014/gbir/_.s -di
	./asm  ../vm_champs/champs/championships/2014/gjestin/salamahenagalabadoun.s -di
	./asm  ../vm_champs/champs/championships/2014/gleger/Machine-gun.s -di
	./asm  ../vm_champs/champs/championships/2014/gmange/corelol.s -di
	./asm  ../vm_champs/champs/championships/2014/gpetrov/MarineKing.s -di
	./asm  ../vm_champs/champs/championships/2014/gudepard/Kappa.s -di
	./asm  ../vm_champs/champs/championships/2014/hmichals/Wall.s -di
	./asm  ../vm_champs/champs/championships/2014/hmoutaou/Misaka_Mikoto.s -di
	./asm  ../vm_champs/champs/championships/2014/kelickel/Varimathras.s -di
	./asm  ../vm_champs/champs/championships/2014/kmonrose/justin_bee.s -di
	./asm  ../vm_champs/champs/championships/2014/ldesgoui/_honeybadger.s -di
	./asm  ../vm_champs/champs/championships/2014/lseguin/skynet.s -di
	./asm  ../vm_champs/champs/championships/2014/lsirigna/live.s -di
	./asm  ../vm_champs/champs/championships/2014/mbacoux/meowluigi.s -di
	./asm  ../vm_champs/champs/championships/2014/mconraux/dubo.s -di
	./asm  ../vm_champs/champs/championships/2014/rabid-on/jinx.s -di
	./asm  ../vm_champs/champs/championships/2014/rmasse/THUNDER.s -di
	./asm  ../vm_champs/champs/championships/2014/sbuono/Asombra.s -di
	./asm  ../vm_champs/champs/championships/2014/srabah-m/littlepuppy.s -di
	./asm  ../vm_champs/champs/championships/2014/tdemay/champ.s -di
	./asm  ../vm_champs/champs/championships/2014/vrey/darksasuke.s -di
	./asm  ../vm_champs/champs/championships/2014/ybouvet/casimir.s -di

err:
	valgrind --track-origins=yes --leak-check=full ./asm ~/Git/Corewar_git/test_files/err_files/Backward.s
	valgrind --track-origins=yes --leak-check=full ./asm ~/Git/Corewar_git/test_files/err_files/err_in_name.s
	valgrind --track-origins=yes --leak-check=full ./asm ~/Git/Corewar_git/test_files/err_files/err_param_%.s
	valgrind --track-origins=yes --leak-check=full ./asm ~/Git/Corewar_git/test_files/err_files/tdc4.s

clean :
	@rm -rf $(OBJS) objs
	@make clean -C $(LIB_PATH)
	@echo "${WHITE}Asm objs		${RED}DEL${WHITE}"

fclean : clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME)
	@echo "${WHITE}Asm status		${RED}DEL${WHITE}"

re : fclean all
