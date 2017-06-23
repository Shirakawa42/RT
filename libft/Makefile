# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 09:58:24 by rmenegau          #+#    #+#              #
#    Updated: 2016/06/10 11:19:58 by rmenegau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
FLAGS=-Wall -Wextra -Werror
INC_PATH=includes/
PTF_PATH=ft_printf/

SRC=ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_isspace.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
	ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_power.c \
	ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
	ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c \
	ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
	ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
	ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
	ft_toupper.c ft_lstcount.c ft_lstaddl.c ft_lstdelone_i.c ft_realloc_p.c \
	ft_atoi_b.c ft_itoa_b.c ft_realloc.c get_next_line.c ft_getnbr.c \
	ft_atol.c \
	conv.c conv_di.c conv_oux.c conv_s.c parkour.c ptf_prec.c split_utf8.c \
	conv_c.c conv_else.c conv_p.c ft_printf.c ptf_chmp.c split_flag.c
OBJ=$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) -I $(INC_PATH) $<

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@printf "\033[0;32mlibft.a compiled\033[0m\n"
clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all
