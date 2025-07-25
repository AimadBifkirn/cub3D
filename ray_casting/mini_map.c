#include "../cube.h"

#define MINIMAP_TILE_SIZE 10
#define MINIMAP_RADIUS 4 // Shows a 9x9 grid
#define MINIMAP_CENTER (MINIMAP_RADIUS * MINIMAP_TILE_SIZE)
#define MINIMAP_POS_X 40
#define MINIMAP_POS_Y 40

void	put_pixels(t_elements *elem, int x, int y)
{
	int	pixel_y;
	int	pixel_x;
	int	color;
	int	draw_x;
	int	draw_y;

	draw_x = (x - (int)elem->player->x) * MINIMAP_TILE_SIZE + MINIMAP_POS_X;
	draw_y = (y - (int)elem->player->y) * MINIMAP_TILE_SIZE + MINIMAP_POS_Y;
	pixel_y = 0;
	if (elem->map->map[y][x] == '1')
		color = 0xCCCCCC;
	else
		color = 0x333333;
	while (pixel_y < MINIMAP_TILE_SIZE)
	{
		pixel_x = 0;
		while (pixel_x < MINIMAP_TILE_SIZE)
		{
			put_pixel_to_image(elem, draw_x + pixel_x, draw_y + pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

t_m_map	init_elements(t_elements *elem)
{
	t_m_map	res;

	res.start_x = (int)(elem->player->x) - MINIMAP_RADIUS;
	res.end_x = (int)(elem->player->x) + MINIMAP_RADIUS;
	res.start_y = (int)(elem->player->y) - MINIMAP_RADIUS;
	res.end_y = (int)(elem->player->y) + MINIMAP_RADIUS;
	if (res.start_x < 0)
		res.start_x = 0;
	if (res.start_y < 0)
		res.start_y = 0;
	if (res.end_x >= elem->map->colomns)
		res.end_x = elem->map->colomns;
	if (res.end_y >= elem->map->rows)
		res.end_y = elem->map->rows;
	return (res);
}

void	draw_background(t_elements *elem)
{
	int	x;
	int	y;
	int max;


	max = (2 * MINIMAP_RADIUS) * MINIMAP_TILE_SIZE;
	y = 0;
	while (y < max)
	{
		x = 0;
		while (x < max)
		{
			put_pixel_to_image(elem, x, y, 0x111111);
			x++;
		}
		y++;
	}
}

void	draw_map(t_elements *elem)
{
	int	x;
	int	y;
	t_m_map mini_m;

	mini_m = init_elements(elem);	

	y = mini_m.start_y;
	while (y < mini_m.end_y && elem->map->map[y])
	{
		x = mini_m.start_x;
		while (x < mini_m.end_x && elem->map->map[y][x])
		{
			put_pixels(elem, x, y);
			x++;
		}
		y++;
	}
}

void	draw_player(t_elements *elem)
{
	int	x;
	int	y;
	int	size;
	int	mini_p_x;
	int	mini_p_y;

	size = 3;
	mini_p_x = MINIMAP_POS_X + MINIMAP_TILE_SIZE / 2;
	mini_p_y = MINIMAP_POS_Y + MINIMAP_TILE_SIZE / 2;
	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			put_pixel_to_image(elem, mini_p_x + (x - 0.5), mini_p_y + (y - 0.5), 0x0000FF);
			x++;
		}
		y++;
	}
}

int	check_bounds(t_elements *elem, double ray_x, double ray_y)
{
	if (elem->map->map[(int)ray_y][(int)ray_x] == '1')
		return (1);
	if (elem->map->map[(int)(ray_y - MOVE_SPEED)][(int)(ray_x - MOVE_SPEED)] == '1')
		return (1);
	if (elem->map->map[(int)(ray_y + MOVE_SPEED)][(int)(ray_x + MOVE_SPEED)] == '1')
		return (1);
	if (elem->map->map[(int)(ray_y + MOVE_SPEED)][(int)(ray_x - MOVE_SPEED)] == '1')
		return (1);
	if (elem->map->map[(int)(ray_y - MOVE_SPEED)][(int)(ray_x + MOVE_SPEED)] == '1')
		return (1);
	return (0);
}

void	cast_multiple_rays(t_elements *elem)
{
	int		num_rays = 60;
	double	start_angle = elem->player->angle - fov / 2;
	double	step_angle = fov / num_rays;
	int		i = 0;
	double	angle;
	double	ray_x;
	double	ray_y;

	while (i < num_rays)
	{
		angle = start_angle + (i * step_angle);
		ray_y = elem->player->y;
		ray_x = elem->player->x;
		while (1)
		{
			ray_x += cos(angle) * MOVE_SPEED;
			ray_y += sin(angle) * MOVE_SPEED;
			if (check_bounds(elem, ray_x, ray_y))
				break ;
			int pixel_x = MINIMAP_POS_X + (ray_x - elem->player->x + 0.5) * MINIMAP_TILE_SIZE;
			int pixel_y = MINIMAP_POS_Y + (ray_y - elem->player->y + 0.5) * MINIMAP_TILE_SIZE;
			if (pixel_x < 0 || pixel_y < 0 || pixel_x >= (2 * MINIMAP_RADIUS * MINIMAP_TILE_SIZE) || pixel_y >= (2 * MINIMAP_RADIUS * MINIMAP_TILE_SIZE))
    			break;
			put_pixel_to_image(elem, pixel_x, pixel_y, 0x00FFFF);
		}
		i++;
	}
}

void	draw_mini_map(t_elements *elem)
{
	draw_background(elem);
	draw_map(elem);
	draw_player(elem);
	cast_multiple_rays(elem);
}
