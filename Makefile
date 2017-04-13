
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/04/11 18:31:42 by rmenegau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = RT
CC = gcc -Wall -Wextra -Werror
SRCS = src/main.c \
    src/vector.c \
    src/create_lights.c \
    src/create_objects.c \
    src/color.c \
    src/intersects.c \
    src/normals.c \
    src/parse.c

FLAGS = -I /Library/Frameworks/SDL2.framework/Headers -L./libft -lft
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)


%.o: %.c
	gcc -c $^ -o $@ -I /Library/Frameworks/SDL2.framework/Headers -I ./includes -I ./libft/

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -lm -F/Library/Frameworks -framework SDL2

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all