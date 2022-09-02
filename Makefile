# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raho <raho@student.hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 18:17:08 by raho              #+#    #+#              #
#    Updated: 2022/09/02 06:15:30 by raho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Add dependancy for header file - if header is modified, rebuild .o files. #
# Same for Makefile changes #

NAME = wolf3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIB = libft/libft.a
LIBFTINCL = libft/
MLXLIB = /usr/local/lib
MLXINCL = /usr/local/include
INCL = wolf3d.h
SRCS = main.c hooks.c open_close_map.c free_mallocs.c set_up_structs.c \
		draw_line.c pixel_handling.c scaling_functions.c handle_map_file.c \
		render.c
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
