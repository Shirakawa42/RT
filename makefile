# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/06/26 14:03:17 by lvasseur         ###   ########.fr        #
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
	  src/lighting.c \
	  src/main2.c \
	  src/main3.c \
	  src/config_co.c \
	  src/config_cyl.c \
	  src/config_hype.c \
	  src/config_plane.c \
	  src/config_sphere.c \
	  src/perlin2.c \
	  src/perlin_init.c \
	  src/perlin_init2.c \
	  src/perlin_init3.c \
	  src/texture2.c \
	  src/init.c \
	  src/cut.c \
	  src/launch2.c

OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./includes -I ./SDL2/include/SDL2/

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -L ./SDL2/lib/ -lSDL2

c clean:
	@make clean -C libft/
	rm -f $(OBJ)

f fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
