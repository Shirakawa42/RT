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
	  src/parser.c\
	  src/launch.c\
	  src/lighting.c \
	  src/perlin_init.c \
	  src/perlin_init2.c \
	  src/perlin_init3.c

OBJ = $(SRC:.c=.o)
	FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./includes

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -lSDL2 -lm -lSDL2_image

c clean:
	rm -f $(OBJ)
	@make clean -C libft/

f fclean: clean
	rm -f $(NAME)
	@make fclean -C libft/

r re: fclean all

g good: $(NAME) clean
