# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/12 14:42:00 by tjacquin          #+#    #+#              #
#    Updated: 2017/06/27 17:40:06 by tjacquin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	RT

CC			=	gcc
FLAGS		=

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)includes/

SRC_DIR		=	src/
INC_DIR		=	includes/
OBJ_DIR		=	objs/

SDL_DIR		=	SDL2-2.0.5
SDL_LIB		=	$(SDL_DIR)/build/.libs/libSDL2.a
SDL_INC		=	$(SDL_DIR)/include/

FLAG_SDL	=	-I/$(SDL_INC) $(SDL_LIB) -framework Cocoa -framework CoreAudio -framework AudioToolbox -framework ForceFeedback -framework CoreVideo -framework Carbon -framework IOKit -liconv


SRC_BASE	=	\
main.c \
vector.c \
create_lights.c \
create_objects.c \
intersects.c \
normals.c \
normals_sphered.c \
perlin.c \
color.c \
matrice.c \
texture.c \
parser.c \
launch.c \
lighting.c \
main2.c \
main3.c \
config_co.c \
config_cyl.c \
config_hype.c \
config_plane.c \
config_sphere.c \
perlin2.c \
perlin_init.c \
perlin_init2.c \
perlin_init3.c \
texture2.c \
init.c \
cut.c \
launch2.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

all : $(NAME)

$(NAME):		$(SDL_LIB) $(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) $(LIBFT_LIB) \
		$(FLAG_SDL) \
		$(FLAGS)
	@echo "\033[1;34mRT is ready to run"

$(LIBFT_LIB):
	@make -j -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(SDL_INC)\
		-I $(LIBFT_INC)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;33mall is clean";

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "\033[3;0;31mall files have been scratched";

re:				fclean all

.PHONY :		fclean clean re

-include $(OBJS:.o=.d)
