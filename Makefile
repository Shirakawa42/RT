# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/04/02 18:08:47 by rmenegau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC = src/main.c
OBJ = $(SRC:.c=.o)
	FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I /Users/rmenegau/Library/Frameworks/SDL2.framework/Headers

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -lm -F/Users/rmenegau/Library/Frameworks -framework SDL2

c clean:
	rm -f $(OBJ)

f fclean: clean
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
