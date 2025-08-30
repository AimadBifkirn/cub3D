# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 18:51:42 by zmounji           #+#    #+#              #
#    Updated: 2025/08/21 10:54:38 by abifkirn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAMEB = cub3D_bonus
CC = cc 
FLAGS = -Wall -Wextra -Werror -g3

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INCLUDES = -I$(MLX_DIR) # optional, if you include mlx.h with "minilibx-linux/mlx.h"

SRC = main.c parcing/parcing_mn.c parcing/extract_map.c parcing/map.c\
	helpers/get_next_line/get_next_line.c helpers/get_next_line/get_next_line_utils.c\
	helpers/libft/ft_bzero.c parcing/upload_map.c helpers/libft/ft_split.c\
	helpers/libft/ft_atoi.c parcing/cheack_map.c ray_casting/ray_cast.c\
	ray_casting/events.c ray_casting/mini_map.c garbagecolector/ga_collector.c\
	getters.c doors_and_animation.c ray_casting/drawing.c ray_casting/texture.c\
	ray_casting/ray_cast_helper.c ray_casting/moves.c ray_casting/rotation.c\
	ray_casting/mini_map_helper.c parcing/map3.c parcing/map2.c\
	parcing/map4.c ray_casting/drawing2.c garbagecolector/garbage_helper.c

SRCB = bonus/main_bonus.c bonus/parcing/parcing_mn_bonus.c bonus/parcing/extract_map_bonus.c bonus/parcing/map_bonus.c\
	bonus/helpers/get_next_line/get_next_line_bonus.c bonus/helpers/get_next_line/get_next_line_utils_bonus.c\
	bonus/helpers/libft/ft_bzero_bonus.c bonus/parcing/upload_map_bonus.c bonus/helpers/libft/ft_split_bonus.c\
	bonus/helpers/libft/ft_atoi_bonus.c bonus/parcing/cheack_map_bonus.c bonus/ray_casting/ray_cast_bonus.c\
	bonus/ray_casting/events_bonus.c bonus/ray_casting/mini_map_bonus.c bonus/garbagecolector/ga_collector_bonus.c\
	bonus/getters_bonus.c bonus/doors_and_animation_bonus.c bonus/ray_casting/drawing_bonus.c bonus/ray_casting/texture_bonus.c\
	bonus/ray_casting/ray_cast_helper_bonus.c bonus/ray_casting/moves_bonus.c bonus/ray_casting/rotation_bonus.c\
	bonus/ray_casting/mini_map_helper_bonus.c bonus/parcing/map3_bonus.c bonus/parcing/map2_bonus.c\
	bonus/parcing/map4_bonus.c bonus/ray_casting/drawing2_bonus.c bonus/garbagecolector/garbage_helper_bonus.c

OBJ = ${SRC:.c=.o}

OBJB = ${SRCB:.c=.o}

%.o: %.c
	${CC} ${FLAGS} $(INCLUDES) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${OBJ} $(MLX_FLAGS) -o ${NAME}

bonus: ${NAMEB}

${NAMEB}: ${OBJB}
	${CC} ${OBJB} $(MLX_FLAGS) -o ${NAMEB}

clean:
	rm -f ${OBJ}
	rm -f ${OBJB}

fclean: clean
	rm -f ${NAME}
	rm -f ${NAMEB}

re: fclean all

.PHONY: all clean fclean re
