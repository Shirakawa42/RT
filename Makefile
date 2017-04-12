# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
<<<<<<< HEAD
#    Created: 2016/02/16 11:16:50 by rmenegau          #+#    #+#              #
#    Updated: 2017/03/22 18:58:41 by rmenegau         ###   ########.fr        #
=======
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/04/11 18:31:42 by rmenegau         ###   ########.fr        #
>>>>>>> 6340679b0a8ccc5b04fe2592e5de52616560db4b
#                                                                              #
# **************************************************************************** #

NAME = RT
<<<<<<< HEAD
SRC = src/main.c
OBJ = $(SRC:.c=.o)
FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o RT $(SRC) includes/rt.h /usr/include/SDL2/SDL.h -lSDL2 -lm
=======
SRC = src/main.c \
	  src/vector.c \
	  src/create_lights.c \
	  src/create_objects.c \
	  src/color.c \
	  src/intersects.c \
	  src/normals.c
OBJ = $(SRC:.c=.o)
	FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I /Users/rmenegau/Library/Frameworks/SDL2.framework/Headers -I ./includes

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -lm -F/Users/rmenegau/Library/Frameworks -framework SDL2
>>>>>>> 6340679b0a8ccc5b04fe2592e5de52616560db4b

c clean:
	rm -f $(OBJ)

f fclean: clean
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
