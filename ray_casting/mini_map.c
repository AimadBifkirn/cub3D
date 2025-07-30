#include "../cube.h"

#define MINIMAP_TILE_SIZE 8
#define MINIMAP_RADIUS 10
#define MINIMAP_SIZE (2 * MINIMAP_RADIUS * MINIMAP_TILE_SIZE)

void put_pixels(t_elements *elem, int x, int y)
{
	int pixel_y = 0;
	int pixel_x = 0;
	int color;
	int draw_x;
	int draw_y;
	double offset_x = x - elem->player->x;
	double offset_y = y - elem->player->y;

	draw_x = (offset_x * MINIMAP_TILE_SIZE) + MINIMAP_SIZE / 2;
	draw_y = (offset_y * MINIMAP_TILE_SIZE) + MINIMAP_SIZE / 2;

	color = (elem->map->map[y][x] == '1') ? 0xCCCCCC : 0x333333;

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

t_m_map init_elements(t_elements *elem)
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

void draw_background(t_elements *elem)
{
	int x = 0;
	int y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			put_pixel_to_image(elem, x, y, 0x111111);
			x++;
		}
		y++;
	}
}

void draw_map(t_elements *elem)
{
	t_m_map mini_m = init_elements(elem);
	// printf ("start = %d || end = %d || columns = %d\n", mini_m.start_x, mini_m.end_x, elem->map->colomns);
	// printf ("start = %d || end = %d || rows = %d\n", mini_m.start_y, mini_m.end_y, elem->map->rows);
	int y = mini_m.start_y;
	while (y < mini_m.end_y && y < 80)
	{
		int x = mini_m.start_x;
		while (x < mini_m.end_x && x < 80)
		{
			put_pixels(elem, x, y);
			x++;
		}
		y++;
	}
}

void draw_player(t_elements *elem)
{
	int size = 3;
	int mini_p_x = MINIMAP_SIZE / 2;
	int mini_p_y = MINIMAP_SIZE / 2;
	int y = -size;
	while (y <= size)
	{
		int x = -size;
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

void cast_multiple_rays(t_elements *elem)
{
	int num_rays = 60;
	double start_angle = elem->player->angle - fov / 2;
	double step_angle = fov / num_rays;
	int i = 0;
	while (i < num_rays)
	{
		double angle = start_angle + (i * step_angle);
		double ray_x = elem->player->x;
		double ray_y = elem->player->y;
		while (1)
		{
			ray_x += cos(angle) * MOVE_SPEED;
			ray_y += sin(angle) * MOVE_SPEED;
			if (check_bounds(elem, ray_x, ray_y))
				break;
			int pixel_x = (ray_x - elem->player->x) * MINIMAP_TILE_SIZE + MINIMAP_SIZE / 2;
			int pixel_y = (ray_y - elem->player->y) * MINIMAP_TILE_SIZE + MINIMAP_SIZE / 2;
			if (pixel_x < 0 || pixel_y < 0 || pixel_x >= MINIMAP_SIZE || pixel_y >= MINIMAP_SIZE)
				break;
			put_pixel_to_image(elem, pixel_x, pixel_y, 0x00FFFF);
		}
		i++;
	}
}

void draw_mini_map(t_elements *elem)
{
	draw_background(elem);
	draw_map(elem);
	draw_player(elem);
	cast_multiple_rays(elem);
}
