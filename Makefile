# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aorji <aorji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/14 18:06:01 by aorji             #+#    #+#              #
#    Updated: 2019/10/14 18:13:14 by aorji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	n_puzzle

OBJ_DIR =   ./obj/
SRC_DIR =   ./src/
INC_DIR =	./inc/

CC      =	clang++
FLAGS   =   -Wall -Wextra -Werror -std=c++11 --debug

SRC     =   main.cpp																						\
			Puzzle.cpp AStar.cpp Exception.cpp
OBJ     =   $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
INC		=	$(INC_DIR)

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -I $(INC)
	echo "\033[32m[ ✔ ] "$(NAME) created" \033[0m"

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	# -c == Compile the source files, but do not link ==> .o
	$(CC) $(FLAGS) $< -c -o $@ 

re:
	make fclean
	make

clean:
	rm -f $(OBJ)
	echo "\033[31m[ × ] "$(OBJ) removed" \033[0m"

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	echo "\033[31m[ × ] "$(NAME) removed" \033[0m"