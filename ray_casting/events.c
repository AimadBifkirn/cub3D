#include "../cube.h"

int is_free(double x, double y, char **map)
{
	double PLAYER_RADIUS = 0.4;
	if (map[(int)(y - PLAYER_RADIUS)][(int)(x - PLAYER_RADIUS)] == '1' ||
		map[(int)(y - PLAYER_RADIUS)][(int)(x + PLAYER_RADIUS)] == '1' ||
		map[(int)(y + PLAYER_RADIUS)][(int)(x - PLAYER_RADIUS)] == '1' ||
		map[(int)(y + PLAYER_RADIUS)][(int)(x + PLAYER_RADIUS)] == '1')
		return (0);
	return (1);
}

void	move_forward(t_elements **elem)
{
	double new_x;
	double new_y;

	new_x = (*elem)->player->x + ((*elem)->player->direction_x * MOVE_SPEED);
	new_y = (*elem)->player->y + ((*elem)->player->direction_y * MOVE_SPEED);
	if (is_free(new_x, new_y, (*elem)->map->map))
	{
		(*elem)->player->x = new_x;
		(*elem)->player->y = new_y;
		render(elem);		
	}
}

void	move_backward(t_elements **elem)
{
	double new_x;
	double new_y;

	new_x = (*elem)->player->x - ((*elem)->player->direction_x * MOVE_SPEED);
	new_y = (*elem)->player->y - ((*elem)->player->direction_y * MOVE_SPEED);
	if (is_free(new_x, new_y, (*elem)->map->map))
	{
		(*elem)->player->x = new_x;
		(*elem)->player->y = new_y;
		render(elem);		
	}
}

void	move_left(t_elements **elem)
{
	double new_x;
	double new_y;

	new_x = (*elem)->player->x + (*elem)->player->direction_y * MOVE_SPEED;
	new_y = (*elem)->player->y - (*elem)->player->direction_x * MOVE_SPEED;
	if (is_free(new_x, new_y, (*elem)->map->map))
	{
		(*elem)->player->x = new_x;
		(*elem)->player->y = new_y;
		render(elem);		
	}
	printf ("hey\n");
}

void	move_right(t_elements **elem)
{
	double new_x;
	double new_y;

	new_x = (*elem)->player->x - (*elem)->player->direction_y * MOVE_SPEED;
	new_y = (*elem)->player->y + (*elem)->player->direction_x * MOVE_SPEED;
	if (is_free(new_x, new_y, (*elem)->map->map))
	{
		(*elem)->player->x = new_x;
		(*elem)->player->y = new_y;
		render(elem);		
	}
}

void	rotate_left(t_elements **elem)
{
	double	old_dir_x;
	double	old_dir_y;

	old_dir_x = (*elem)->player->direction_x;
	old_dir_y = (*elem)->player->direction_y;

	(*elem)->player->direction_x = old_dir_x * cos(-ROT_SPEED) - old_dir_y * sin(-ROT_SPEED);
	(*elem)->player->direction_y = old_dir_x * sin(-ROT_SPEED) + old_dir_y * cos(-ROT_SPEED);
	(*elem)->player->angle -= ROT_SPEED;
	render(elem);
}

void	rotate_right(t_elements **elem)
{
	double	old_dir_x;
	double	old_dir_y;

	old_dir_x = (*elem)->player->direction_x;
	old_dir_y = (*elem)->player->direction_y;

	(*elem)->player->direction_x = old_dir_x * cos(ROT_SPEED) - old_dir_y * sin(ROT_SPEED);
	(*elem)->player->direction_y = old_dir_x * sin(ROT_SPEED) + old_dir_y * cos(ROT_SPEED);
	(*elem)->player->angle += ROT_SPEED;
	render(elem);
}

int	event_handeler(int code, t_elements **elem)
{
	if (code == 'w')
		move_forward(elem);
	if (code == 's')
		move_backward(elem);
	if (code == 'a')
		move_left(elem);
	if (code == 'd')
		move_right(elem);
	if (code == 65361) // Left arrow
		rotate_left(elem);
	if (code == 65363) // Right arrow
		rotate_right(elem);
	return (0);
}
