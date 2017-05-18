# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2017/05/17 12:59:21 by lvasseur         ###   ########.fr        #
=======
#    Updated: 2017/05/17 16:06:15 by lomeress         ###   ########.fr        #
>>>>>>> b9aba860b5986e5c6c48e5bdb9f66190da6378ac
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
<<<<<<< HEAD
      src/parse.c \
      src/interprete_values.c \
      src/put_in_fcts.c \
=======
>>>>>>> b9aba860b5986e5c6c48e5bdb9f66190da6378ac
	  src/texture.c\

OBJ = $(SRC:.c=.o)
		FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
<<<<<<< HEAD
	gcc -c $^ -o $@ -I ./includes -I /Users/lvasseur/.brew/Cellar/sdl2/2.0.5/include/SDL2/

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -L /Users/lvasseur/.brew/Cellar/sdl2/2.0.5/lib/ -lSDL2
=======
	gcc -c $^ -o $@ -I ./includes -I /Users/lomeress/.brew/Cellar/sdl2/2.0.5/include/SDL2/

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -L /Users/lomeress/.brew/Cellar/sdl2/2.0.5/lib/ -lSDL2
>>>>>>> b9aba860b5986e5c6c48e5bdb9f66190da6378ac

c clean:
	@make clean -C libft/
	rm -f $(OBJ)

f fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
