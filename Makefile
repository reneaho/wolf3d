# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raho <raho@student.hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 18:17:08 by raho              #+#    #+#              #
#    Updated: 2022/12/17 07:40:21 by raho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Add dependancy for header file - if header is modified, rebuild .o files. #
# Same for Makefile changes #

NAME = wolf3d
CC = gcc
CFLAGS = -g -O2
LIB = libft/libft.a
LIBFTINCL = libft/
MLXLIB = /usr/local/lib
MLXINCL = /usr/local/include
INCL = wolf3d.h
SRCS = main.c hooks.c open_close_map.c init_textures.c \
		 pixel_handling.c handle_map_file.c \
		render.c raycast.c raycast_horizontal.c raycast_vertical.c \
		draw.c
OBJS = $(SRCS:.c=.o)
MLXLINK = -lmlx -framework OpenGL -framework Appkit

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -I $(LIBFTINCL) -I $(MLXINCL) \
	-I $(INCL) $(MLXLINK) -o $(NAME)

$(LIB):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
