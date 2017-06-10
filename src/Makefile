# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/05/24 14:40:53 by lomeress         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC = main.c \
	  vector.c \
	  create_lights.c \
	  create_objects.c \
	  intersects.c \
	  normals.c \
	  normals_sphered.c \
	  perlin.c \
	  color.c \
	  matrice.c \
	  texture.c\
	  parser.c\
	  launch.c\
	  lighting.c\
	  perlin_init.c\
	  perlin_init2.c\
	  perlin_init3.c

OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./includes -I $(HOME)/.brew/Cellar/sdl2/2.0.5/include/

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft.a -L $(HOME)/.brew/Cellar/sdl2/2.0.5/lib/ -lSDL2

c clean:
	rm -f $(OBJ)

f fclean: clean
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean