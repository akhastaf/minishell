# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 10:55:58 by akhastaf          #+#    #+#              #
#    Updated: 2020/11/24 12:09:42 by akhastaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = gcc
FLAGS = -Wall -Wextra -Werror
NAME = minishell
D = -g
SRC = ./src/*.c ./src/*/*.c
OBJ = minishell

all: $(NAME)

$(NAME):
	@$(C) -g -o $(NAME) main.c $(SRC)

debug:
	@$(C) $(FLAGS) -o $(NAME) main.c $(SRC) -fsanitize=address

clean:
	@rm -f $(NAME)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all