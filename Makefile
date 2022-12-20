# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raho <raho@student.hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 18:17:08 by raho              #+#    #+#              #
#    Updated: 2022/12/20 13:52:35 by raho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIB = libft/libft.a
LIBFTINCL = libft/
MLXLIB = /usr/local/lib
MLXINCL = /usr/local/include
INCL = wolf3d.h
SRCS = get_map_dimensions.c draw.c errors.c hooks.c init_textures.c main.c \
		player_movement.c raycast_horizontal.c raycast_vertical.c raycast.c \
		save_map.c validate_map.c
OBJS = $(SRCS:.c=.o)
MLXLINK = -lmlx -framework OpenGL -framework Appkit

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIB) $(INCL)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -I $(LIBFTINCL) -I $(MLXINCL) \
	-I $(INCL) $(MLXLINK) -o $(NAME) -lm

$(LIB):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
