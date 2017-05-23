# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/05/18 18:33:05 by yismail          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
CC = gcc -Wall -Wextra -Werror
SRC = src/main.c \
	  src/vector.c \
	  src/create_lights.c \
	  src/create_objects.c \
	  src/intersects.c \
	  src/normals.c \
	  src/perlin.c \
	  src/color.c \
	  src/matrice.c \
	  src/texture.c \
	 src/parser.c
OBJ = $(SRC:.c=.o)
		FLAGS = -I /Library/Frameworks/SDL2.framework/Headers -L./libft -lft

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I /Library/Frameworks/SDL2.framework/Headers -I ./includes -I ./libft/

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) -lm -F/Library/Frameworks -framework SDL2

c clean:
	@make clean -C libft/
	rm -f $(OBJ)

f fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
