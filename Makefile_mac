# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/05/23 09:33:42 by rmenegau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC = src/main.c \
	  src/vector.c \
	  src/create_lights.c \
	  src/create_objects.c \
	  src/intersects.c \
	  src/normals.c \
	  src/normals_sphered.c \
	  src/perlin.c \
	  src/color.c \
	  src/matrice.c \
	  src/texture.c\
	  src/parser.c\
	  src/launch.c\
	  src/lighting.c

OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./includes -I $(HOME)/.brew/Cellar/sdl2/2.0.5/include/

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -L $(HOME)/.brew/Cellar/sdl2/2.0.5/lib/ -lSDL2

c clean:
	@make clean -C libft/
	rm -f $(OBJ)

f fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
