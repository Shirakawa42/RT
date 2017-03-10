# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/03/10 16:23:07 by lomeress         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: make all clean fclean re

NAME = RT

LIB = -L libft/ -lft

LIBFT = libft/libft.a

C_DIR = src/

SRCS = main.c

SRC = $(addprefix $(C_DIR), $(SRCS))

OBJ = $(SRCS:.c=.o)

INC = -I includes/ -I libft/

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc -Wall -Wextra -Werror $^ -o $@ $(LIB) -lmlx -framework OpenGL -framework AppKit

$(LIBFT):
	make -C libft/

$(OBJ) : $(SRC)
	gcc -c -Wall -Wextra -Werror $^ $(INC)

clean :
	make clean -C libft/
	rm -f $(OBJ)

fclean : clean
	make fclean -C libft/
	rm -f $(NAME)

re : fclean all

good: all clean
