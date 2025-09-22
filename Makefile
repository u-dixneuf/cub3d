# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzary <mzary@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/19 18:28:02 by mzary             #+#    #+#              #
#    Updated: 2025/09/22 17:07:05 by mzary            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DO NOT FORGET!!
# ADD MAMAZIAN HEADERS IN PARSING FILES

# CHECK THAT ALL FUNCTIONS THAT SHOULD
# BE STATIC ARE STATIC

NAME = 	cub3D

CC 	= 	cc #-Wall -Wextra -Werror
HDR =	cub3d.h
SRC = 	main.c \
		src/tools/string.c \
		src/tools/mlxinit.c \
		src/tools/mlxdestroy.c \
		src/tools/csplit.c \
		src/tools/cgetline.c \
		src/tools/cerror.c \
		src/tools/catoi.c \
		src/map/mapinit.c \
		src/map/mapdestroy.c \
		src/map/parsedata.c \
		src/map/parsegrid.c \
		src/map/gridutils.c \
		src/game/game.c
OBJ =	$(SRC:.c=.o)
MLX =	mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(CC) $^ -lXext -lX11 -lm -o $@

%.o: %.c $(HDR)
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean