# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/05/21 12:12:16 by rmenegau         ###   ########.fr        #
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
	  src/launch.c\
	  src/lighting.c \
	  src/perlin_init.c \
	  src/perlin_init2.c \
	  src/perlin_init3.c \
	  src/texture2.c \
	  src/main2.c \
	  src/main3.c \
	  src/launch2.c \
	  src/config_co.c \
	  src/config_cyl.c \
	  src/config_hype.c \
	  src/config_plane.c \
	  src/config_sphere.c \
	  src/init.c \
	  src/perlin2.c \
	  src/cut.c \
	  src/parser_1.c \
	  src/parser_2.c \
	  src/parse_obj_1.c \
	  src/parse_obj_2.c \
	  src/parse_obj_3.c \
	  src/parser_init.c

OBJ = $(SRC:.c=.o)
	FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./includes

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -lSDL2 -lm -lpthread

c clean:
	rm -f $(OBJ)
	@make clean -C libft/

f fclean: clean
	rm -f $(NAME)
	@make fclean -C libft/

r re: fclean all

g good: $(NAME) clean
