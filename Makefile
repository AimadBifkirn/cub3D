NAME = cub3D
CC = cc 
FLAGS = -Wall -Wextra -Werror  -g3

SRC = main.c parcing/parcing_mn.c parcing/extract_map.c parcing/map.c\
	helpers/get_next_line/get_next_line.c helpers/get_next_line/get_next_line_utils.c\
	helpers/libft/ft_bzero.c parcing/upload_map.c helpers/libft/ft_split.c\
	helpers/libft/ft_atoi.c parcing/cheack_map.c ray_casting/ray_cast.c #raycasting/raycasting.c \
	debug_map/map.c 


OBJ = ${SRC:.c=.o}

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME}


${NAME}: ${OBJ}
	${CC}  ${OBJ} -lmlx -lXext -lX11 -lm  -o ${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all


.PHONY: all clean fclean re
.SECONDARY: