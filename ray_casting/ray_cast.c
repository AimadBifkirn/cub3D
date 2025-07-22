#include "../cube.h"

// void	cast_single_ray(t_elements *elem)
// {
// 	double	ray_x = elem->player->x;
// 	double	ray_y = elem->player->y;
// 	double	dir_x = elem->player->direction_x;
// 	double	dir_y = elem->player->direction_y;
// 	double	step_size = 0.05;

// 	while (1)
// 	{
// 		ray_x += dir_x * step_size;
// 		ray_y += dir_y * step_size;

// 		int map_x = (int)ray_x;
// 		int map_y = (int)ray_y;

// 		if (elem->map->map[map_y][map_x] == '1')
// 			break ;
// 		int pixel_x = ray_x * square_size;
// 		int pixel_y = ray_y * square_size;
// 		mlx_pixel_put(elem->mlx, elem->wind, pixel_x, pixel_y, 0xFF00FF);
// 	}
// }

void	put_pixel_to_image(t_elements *elem, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= 800 || y >= 600)
		return ;

	dst = elem->addr + (y * elem->line_len + x * (elem->bits_per_px / 8));
	*(unsigned int *)dst = color;
}

// void	draw_direction_line(t_elements *elem)
// {
// 	int		line_lenght;
// 	int		i;
// 	double	x;
// 	double	y;

// 	line_lenght = 20;
// 	i = 0;
// 	while (i < line_lenght)
// 	{
// 		x = (elem->player->x * square_size - 0.5) + (elem->player->direction_x * i);
// 		y = (elem->player->y * square_size - 0.5) + (elem->player->direction_y * i);
// 		put_pixel_to_image(elem, x, y, 0xFFFF00);
// 		i++;
// 	}
// }

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
			put_pixel_to_image(elem, real_x + (x - 0.5), real_y + (y - 0.5), 0x0000FF);
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

void	get_player_direction(t_elements *elem)
{
	int	p_x;
	int	p_y;

	p_x = (int)(elem->player->x);
	p_y = (int)(elem->player->y);
	if (elem->map->map[p_y][p_x] == 'N')
	{
		// elem->player->direction_x = 0;
		// elem->player->direction_y = -1;
		elem->player->angle = -(PI / 2);
	}
	else if (elem->map->map[p_y][p_x] == 'S')
	{
		// elem->player->direction_x = 0;
		// elem->player->direction_y = 1;
		elem->player->angle = (PI / 2);
	}
	else if (elem->map->map[p_y][p_x] == 'E')
	{
		// elem->player->direction_x = 1;
		// elem->player->direction_y = 0;
		elem->player->angle = 0;
	}
	else if (elem->map->map[p_y][p_x] == 'W')
	{
		// elem->player->direction_x = -1;
		// elem->player->direction_y = 0;
		elem->player->angle = PI;
	}
}

void	get_player_pos(t_elements *elem)
{
	int	x;
	int	y;

	y = 0;
	while (elem->map->map[y])
	{
		x = 0;
		while (elem->map->map[y][x])
		{
			if (elem->map->map[y][x] == 'N' || elem->map->map[y][x] == 'S' 
			|| elem->map->map[y][x] == 'W' || elem->map->map[y][x] == 'E')
			{
				elem->player->x = x + 0.5;
				elem->player->y = y + 0.5;
				get_player_direction(elem);
				return ;
			}
			x++;
		}
		y++;
	}
}

// void	cast_multiple_rays(t_elements *elem)
// {
// 	int		num_rays = 60;
// 	double	start_angle = elem->player->angle - fov / 2;
// 	double	step_angle = fov / num_rays;
// 	int		i = 0;
// 	double	step_size = 0.05;
// 	double	angle;
// 	double	ray_x;
// 	double	ray_y;

// 	while (i < num_rays)
// 	{
// 		angle = start_angle + (i * step_angle);
// 		ray_y = elem->player->y;
// 		ray_x = elem->player->x;
// 		while (1)
// 		{
// 			ray_x += cos(angle) * step_size;
// 			ray_y += sin(angle) * step_size;
// 			if (elem->map->map[(int)ray_y][(int)ray_x] == '1')
// 				break ;
// 			put_pixel_to_image(elem, ray_x * square_size, ray_y * square_size, 0x00FFFF);
// 		}
// 		i++;
// 	}
// }


// void	cast_multiple_rays(t_elements *elem)
// {
// 	int		num_rays = screen_width;
// 	double	start_angle = elem->player->angle - (fov / 2.0);
// 	double	step_angle = fov / num_rays;
// 	int i = 0;

// 	while (i < num_rays)
// 	{
// 		double angle = start_angle + i * step_angle;
// 		// Direction of ray
// 		double ray_dir_x = cos(angle);
// 		double ray_dir_y = sin(angle);
// 		// Which square in the map the player is in
// 		int map_x = (int)elem->player->x;
// 		int map_y = (int)elem->player->y;
// 		// Length of ray from one x or y side to next x or y side
// 		double delta_dist_x = fabs(1 / ray_dir_x);
// 		double delta_dist_y = fabs(1 / ray_dir_y);
// 		// Calculate step and initial sideDist
// 		double side_dist_x;
// 		double side_dist_y;
// 		int step_x;
// 		int step_y;
// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (elem->player->x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - elem->player->x) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (elem->player->y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - elem->player->y) * delta_dist_y;
// 		}
// 		// Perform DDA
// 		int hit = 0;
// 		int side;
// 		while (!hit)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (elem->map->map[map_y][map_x] == '1')
// 				hit = 1;
// 		}
// 		// Calculate distance to wall
// 		double distance;
// 		if (side == 0)
// 			distance = (map_x - elem->player->x + (1 - step_x) / 2.0) / ray_dir_x;
// 		else
// 			distance = (map_y - elem->player->y + (1 - step_y) / 2.0) / ray_dir_y;
// 		// Fix fish-eye distortion
// 		distance *= cos(angle - elem->player->angle);
// 		// Calculate projected wall height
// 		int wall_height = (int)(screen_height / distance);
// 		int wall_top = (screen_height / 2) - (wall_height / 2);
// 		int wall_bottom = (screen_height / 2) + (wall_height / 2);
// 		// Clamp to screen
// 		if (wall_top < 0)
// 			wall_top = 0;
// 		if (wall_bottom > screen_height)
// 			wall_bottom = screen_height;
// 		// Shade depending on wall side
// 		int color = (side == 0) ? 0xCCCCCC : 0x888888;
// 		// Draw vertical line
// 		for (int y = wall_top; y < wall_bottom; y++)
// 			put_pixel_to_image(elem, i, y, color);
// 		i++;
// 	}
// }

void	initalize_draw_elems(t_draw *darw, int i)
{
	darw->ray_dir_x = cos(darw->start_angle + i *  darw->step_angle); // draw.start_angle + i *  draw.step_angle = ray_angle
	darw->ray_dir_y = sin(darw->start_angle + i *  darw->step_angle);
	darw->delta_dist_x = fabs(1 / darw->ray_dir_x);
	darw->delta_dist_y = fabs(1 / darw->ray_dir_y);
	if (darw->ray_dir_x < 0)
	{
		darw->step_x = -1;
		side_dist_x = (player_x - map_x) * darw->delta_dist_x; // hta tkmel hadchi awdi a ana
	}
	else
		darw->step_x = 1;
	if (darw->ray_dir_y < 0)
		darw->step_y = -1;
	else
		darw->step_y = 1;
}

void	cast_multiple_rays(t_elements *elem)
{
	int		i;
	t_draw	draw;

	i = 0;
	draw.start_angle = elem->player->angle - (fov / 2.0);
	draw.step_angle = fov / screen_width;
	while (i < screen_width)
	{
		initalize_draw_elems(&draw, i);
		i++;
	}
}

void	render(t_elements *elem)
{
	int ceiling_color = (elem->c->a << 16) | (elem->c->b << 8) | elem->c->c;
	int floor_color = (elem->f->a << 16) | (elem->f->b << 8) | elem->f->c;

	for (int y = 0; y < 600; y++)
	{
		int color = (y < 600 / 2) ? ceiling_color : floor_color;
		for (int x = 0; x < 800; x++)
			put_pixel_to_image(elem, x, y, color);
	}
	cast_multiple_rays(elem);
	mlx_put_image_to_window(elem->mlx, elem->wind, elem->img, 0, 0);
}


void	load_textures(t_elements *elem)
{
	int i;

	i = 0;
	elem->textures[0].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/wall_1.xpm", &elem->textures[0].width, &elem->textures[0].height);
	elem->textures[1].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/wall_2.xpm", &elem->textures[1].width, &elem->textures[1].height);
	elem->textures[2].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/wall_3.xpm", &elem->textures[2].width, &elem->textures[2].height);
	elem->textures[3].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/wall_4.xpm", &elem->textures[3].width, &elem->textures[3].height);

	while (i < 4)
	{
		if (!elem->textures[i].img_ptr)
		{
			printf ("Failed to load texture n : %d\n", i);
			exit (1);//need to free all the memory before exiting, attention |:
		}
		elem->textures[i].addr = (int *)mlx_get_data_addr(elem->textures[i].img_ptr,
			&elem->textures[i].bpp, &elem->textures[i].line_len, &elem->textures[i].endian);
		i++;
	}
}


void	ray_casting(t_elements *elem)
{
	elem->player = malloc(sizeof(t_player));
	get_player_pos(elem);
	load_textures(elem);
	// elem->player->plane_x = -elem->player->direction_y * fov;
	// elem->player->plane_y =  elem->player->direction_x * fov;
	render(elem);
}
