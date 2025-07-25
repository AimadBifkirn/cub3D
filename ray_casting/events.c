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

void	move_forward(t_elements *elem, int *check)
{
	double new_x = elem->player->x + cos(elem->player->angle) * MOVE_SPEED;
	double new_y = elem->player->y + sin(elem->player->angle) * MOVE_SPEED;

	if (is_free(new_x, new_y, elem->map->map))
	{
		elem->player->x = new_x;
		elem->player->y = new_y;
	}
	else
		*check = 1;
}

void	move_backward(t_elements *elem, int *check)
{
	double new_x = elem->player->x - cos(elem->player->angle) * MOVE_SPEED;
	double new_y = elem->player->y - sin(elem->player->angle) * MOVE_SPEED;

	if (is_free(new_x, new_y, elem->map->map))
	{
		elem->player->x = new_x;
		elem->player->y = new_y;
	}
	else
		*check = 1;
}

void	move_left(t_elements *elem, int *check)
{
	double angle = elem->player->angle - PI / 2;
	double new_x = elem->player->x + cos(angle) * MOVE_SPEED;
	double new_y = elem->player->y + sin(angle) * MOVE_SPEED;

	if (is_free(new_x, new_y, elem->map->map))
	{
		elem->player->x = new_x;
		elem->player->y = new_y;
	}
	else
		*check = 1;
}

void	move_right(t_elements *elem, int *check)
{
	double angle = elem->player->angle + PI / 2;
	double new_x = elem->player->x + cos(angle) * MOVE_SPEED;
	double new_y = elem->player->y + sin(angle) * MOVE_SPEED;

	if (is_free(new_x, new_y, elem->map->map))
	{
		elem->player->x = new_x;
		elem->player->y = new_y;
	}
	else
		*check = 1;
}

void	rotate_left(t_elements *elem)
{
	elem->player->angle -= ROT_SPEED;
	if (elem->player->angle < 0)
		elem->player->angle += 2 * PI;
}

void	rotate_right(t_elements *elem)
{
	elem->player->angle += ROT_SPEED;
	if (elem->player->angle > 2 * PI)
		elem->player->angle -= 2 * PI;
}


int	event_handeler(int code, t_elements *elem)
{
	int	check;

	check = 0;
	if (code == 65361) // Left arrow
		rotate_left(elem);
	else if (code == 65363) // Right arrow
		rotate_right(elem);
	else if (code == 'w')
		move_forward(elem, &check);
	else if (code == 's')
		move_backward(elem, &check);
	else if (code == 'a')
		move_left(elem, &check);
	else if (code == 'd')
		move_right(elem, &check);
	if (check == 0)
		render(elem);
	return (0);
}