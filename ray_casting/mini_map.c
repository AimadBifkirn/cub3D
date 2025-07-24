#include "../cube.h"

void	put_pixels(t_elements *elem, int x, int y)
{
	int	pixel_y;
	int	pixel_x;
	int	color;

	pixel_y = 0;
	if (elem->map->map[y][x] == '1')
		color = 0xCCCCCC;
	else
		color = 0x333333;
	while (pixel_y < square_size)
	{
		pixel_x = 0;
		while (pixel_x < square_size)
		{
			put_pixel_to_image(elem, x * square_size + pixel_x,\
			y *square_size + pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_map(t_elements *elem)
{
	int	x;
	int	y;

	y = 0;
	while (elem->map->map[y])
	{
		x = 0;
		while (elem->map->map[y][x])
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
	int	real_x;
	int	real_y;

	size = 3;
	real_x = elem->player->x * square_size;
	real_y = elem->player->y * square_size;
	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			put_pixel_to_image(elem, real_x + (x - 0.5), real_y + (y - 0.5), 0x0000FF);
			x++;
		}
		y++;
	}
}

void	cast_multiple_rays(t_elements *elem)
{
	int		num_rays = 60;
	double	start_angle = elem->player->angle - fov / 2;
	double	step_angle = fov / num_rays;
	int		i = 0;
	double	step_size = 0.05;
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
			ray_x += cos(angle) * step_size;
			ray_y += sin(angle) * step_size;
			if (elem->map->map[(int)(ray_y - step_size)][(int)(ray_x - step_size)] == '1')
				break ;
			if (elem->map->map[(int)ray_y][(int)ray_x] == '1')
				break ;
			put_pixel_to_image(elem, ray_x * square_size, ray_y * square_size, 0x00FFFF);
		}
		i++;
	}
}

void	draw_mini_map(t_elements *elem)
{
	draw_map(elem);
	draw_player(elem);
	cast_multiple_rays(elem);
}
