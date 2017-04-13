# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/13 12:59:59 by lvasseur          #+#    #+#              #
#    Updated: 2017/04/13 17:44:13 by lvasseur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC = src/main.c \
	  src/create_lights.c \
	  src/create_objects.c \
	  src/intersects.c \
	  src/normals.c \
	  src/vector.c
OBJ = $(SRC:.c=.o)
FLAGS = #-Wall -Wextra -Werror

SDL = -L /Users/lvasseur/.brew/Cellar/sdl2/2.0.5/lib -lSDL2
SDL_INC = -I /Users/lvasseur/.brew/Cellar/sdl2/2.0.5/include/SDL2/

all: $(NAME)

%.o: %.c
	gcc -o $@ -c $< $(SDL_INC) $(FLAGS)

$(NAME): $(OBJ)
	gcc -o $(NAME) $^ -lm  $(SDL) $(FLAGS)

c clean:
	rm -f $(OBJ)

f fclean: clean
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
