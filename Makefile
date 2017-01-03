# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnguyen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/29 17:56:03 by nnguyen           #+#    #+#              #
#    Updated: 2016/12/09 13:54:27 by lwang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = position.c solve.c check.c main.c read.c

OBJ = $(SRC : .c = .o)

LIB = ./libft/libft.a

all: $(NAME)

$(OBJ): ($SRC)
	gcc -Wall -Werror -Wextra -o $(SRC)

$(LIB): 
	@$(MAKE) -C ./libft

$(NAME): $(OBJ) $(LIB)
	@gcc -Wall -Werror -Wextra -o $(NAME) $(SRC) $(OBJ) $(LIB)
	@echo "\033[32mfillit is created\033[0m"
	@echo "\033[33m----------------------\033[0m"

clean:
	@rm -rf $(NAME)
	@$(MAKE) -C ./libft/ clean

fclean: clean
	@echo "\033[33m----------------------\033[0m"
	@$(MAKE) -C ./libft/ fclean
	@echo "\033[32mfclean is done\033[32m"

re: fclean all
