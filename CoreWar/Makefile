# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/19 22:24:46 by mmanley           #+#    #+#              #
#    Updated: 2018/06/19 22:48:06 by mmanley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CORE = corewar

ASM = asm

GREEN = \x1b[32m

WHITE = \x1b[0m

all : $(CORE) $(ASM) info

$(CORE) :
	@make -C core

$(ASM) :
	@make -C asmb

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
