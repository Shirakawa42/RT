# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/05/04 15:42:29 by lvasseur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC = src/main.c \
	  src/vector.c \
	  src/create_lights.c \
	  src/create_objects.c \
	  src/intersects.c \
	  src/normals.c \
	  src/texture.c \
	  src/color.c \
	  src/matrice.c
OBJ = $(SRC:.c=.o)
	FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./includes -I /Users/lvasseur/.brew/Cellar/sdl2/2.0.5/include/SDL2/

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -L /Users/lvasseur/.brew/Cellar/sdl2/2.0.5/lib/ -lSDL2

c clean:
	rm -f $(OBJ)

f fclean: clean
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
