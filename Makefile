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
SRC = src/main.c \
	  src/vector.c \
	  src/create_lights.c \
	  src/create_objects.c \
	  src/intersects.c \
	  src/normals.c \
	  src/perlin.c \
	  src/color.c \
	  src/matrice.c \
	  src/texture.c\
	  src/parse.c \
	  src/interprete_values.c \
	  src/put_in_struct.c
OBJ = $(SRC:.c=.o)
		FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./includes -I /Users/yismail/.brew/Cellar/sdl2/2.0.5/include/SDL2/

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -L /Users/yismail/.brew/Cellar/sdl2/2.0.5/lib/ -lSDL2

c clean:
	@make clean -C libft/
	rm -f $(OBJ)

f fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
