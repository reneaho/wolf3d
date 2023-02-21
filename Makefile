# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raho <raho@student.hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 18:17:08 by raho              #+#    #+#              #
#    Updated: 2023/02/21 15:27:55 by raho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
LIB = libft/libft.a
MLXLIB = /usr/local/lib
MLXINCL = /usr/local/include
SOURCE = get_map_dimensions.c draw.c errors.c hooks.c init_textures.c main.c \
		player_movement.c raycast_horizontal.c raycast_vertical.c raycast.c \
		save_map.c validate_map.c
SRC = $(addprefix source/,$(SOURCE))
OBJ = $(SRC:.c=.o)
INCLUDE = -Iinclude -I $(MLXINCL) -Ilibft
MLXLINK = -lmlx -framework OpenGL -framework Appkit
CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(OBJ) $(LIB) $(INCLUDE) $(MLXLINK) -o $(NAME)

$(LIB):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
