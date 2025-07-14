#include "../cube.h"

void	cast_single_ray(t_elements *elem)
{
	double	ray_x = elem->player->x;
	double	ray_y = elem->player->y;
	double	dir_x = elem->player->direction_x;
	double	dir_y = elem->player->direction_y;
	double	step_size = 0.05;

	while (1)
	{
		ray_x += dir_x * step_size;
		ray_y += dir_y * step_size;

		int map_x = (int)ray_x;
		int map_y = (int)ray_y;

		if (elem->map->map[map_y][map_x] == '1')
			break ;
		int pixel_x = ray_x * square_size;
		int pixel_y = ray_y * square_size;
		mlx_pixel_put(elem->mlx, elem->wind, pixel_x, pixel_y, 0xFF00FF);
	}
}


void	draw_direction_line(t_elements *elem)
{
	int		line_lenght;
	int		i;
	double	x;
	double	y;

	line_lenght = 20;
	i = 0;
	while (i < line_lenght)
	{
		x = (elem->player->x * square_size - 0.5) + (elem->player->direction_x * i);
		y = (elem->player->y * square_size - 0.5) + (elem->player->direction_y * i);
		mlx_pixel_put(elem->mlx, elem->wind, x, y, 0xFFFF00);
		i++;
	}
}

void	draw_player(t_elements *elem)
{
	int	x;
	int	y;
	int	size;
	int	real_x;
	int	real_y;

	size = 4;
	real_x = elem->player->x * square_size;
	real_y = elem->player->y * square_size;
	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			mlx_pixel_put(elem->mlx, elem->wind, real_x + (x - 0.5), real_y + (y - 0.5), 0x0000FF);
			x++;
		}
		y++;
	}
}

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
			mlx_pixel_put(elem->mlx, elem->wind, x * square_size + pixel_x,\
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

void	get_player_direction(t_elements **elem)
{
	int	p_x;
	int	p_y;

	p_x = (int)((*elem)->player->x);
	p_y = (int)((*elem)->player->y);
	if ((*elem)->map->map[p_y][p_x] == 'N')
	{
		(*elem)->player->direction_x = 0;
		(*elem)->player->direction_y = -1;
		(*elem)->player->angle = -(PI / 2);
	}
	else if ((*elem)->map->map[p_y][p_x] == 'S')
	{
		(*elem)->player->direction_x = 0;
		(*elem)->player->direction_y = 1;
		(*elem)->player->angle = (PI / 2);
	}
	else if ((*elem)->map->map[p_y][p_x] == 'E')
	{
		(*elem)->player->direction_x = 1;
		(*elem)->player->direction_y = 0;
		(*elem)->player->angle = 0;
	}
		else if ((*elem)->map->map[p_y][p_x] == 'W')
	{
		(*elem)->player->direction_x = -1;
		(*elem)->player->direction_y = 0;
		(*elem)->player->angle = PI;
	}
}

void	get_player_pos(t_elements **elem)
{
	int	x;
	int	y;

	y = 0;
	while ((*elem)->map->map[y])
	{
		x = 0;
		while ((*elem)->map->map[y][x])
		{
			if ((*elem)->map->map[y][x] == 'N' || (*elem)->map->map[y][x] == 'S' 
			|| (*elem)->map->map[y][x] == 'W' || (*elem)->map->map[y][x] == 'E')
			{
				(*elem)->player->x = x + 0.5;
				(*elem)->player->y = y + 0.5;
				get_player_direction(elem);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	cast_multiple_rays(t_elements *elem)
{
	int		num_rays = 60;
	double	fov = PI / 3; // 60° field of view
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
			if (elem->map->map[(int)ray_y][(int)ray_x] == '1')
				break ;
			mlx_pixel_put(elem->mlx, elem->wind, ray_x * square_size, ray_y * square_size, 0x00FFFF);
		}
		i++;
	}
}

void	ray_casting(t_elements **elem)
{
	(*elem)->player = malloc(sizeof(t_player));
	get_player_pos(elem);
	draw_map(*elem);
	draw_player(*elem);
	draw_direction_line(*elem);
	cast_single_ray(*elem);
	cast_multiple_rays(*elem);
}
