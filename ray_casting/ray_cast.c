#include "../cube.h"

void	put_pixel_to_image(t_elements *elem, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= screen_width || y >= screen_height)
		return ;

	dst = elem->addr + (y * elem->line_len + x * (elem->bits_per_px / 8));
	*(unsigned int *)dst = color;
}

void	get_player_direction(t_elements *elem)
{
	int	p_x;
	int	p_y;

	p_x = (int)(elem->player->x);
	p_y = (int)(elem->player->y);
	if (elem->map->map[p_y][p_x] == 'N')
		elem->player->angle = -(PI / 2);
	else if (elem->map->map[p_y][p_x] == 'S')
		elem->player->angle = (PI / 2);
	else if (elem->map->map[p_y][p_x] == 'E')
		elem->player->angle = 0;
	else if (elem->map->map[p_y][p_x] == 'W')
		elem->player->angle = PI;
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

void	initalize_draw_elems(t_draw *darw, int i, t_elements *elem)
{
	darw->ray_angle = darw->start_angle + i *  darw->step_angle;
	darw->ray_dir_x = cos(darw->ray_angle); // draw.start_angle + i *  draw.step_angle = ray_angle
	darw->ray_dir_y = sin(darw->start_angle + i *  darw->step_angle);
	darw->delta_dist_x = fabs(1 / darw->ray_dir_x);
	darw->delta_dist_y = fabs(1 / darw->ray_dir_y);
	darw->map_x = (int)elem->player->x;
	darw->map_y = (int)elem->player->y;
	if (darw->ray_dir_x < 0)
	{
		darw->step_x = -1;
		darw->side_dist_x = (elem->player->x - darw->map_x) * darw->delta_dist_x;
	}
	else
	{
		darw->step_x = 1;
		darw->side_dist_x = (darw->map_x + 1.0 - elem->player->x) * darw->delta_dist_x;
	}
	if (darw->ray_dir_y < 0)
	{
		darw->step_y = -1;
		darw->side_dist_y = (elem->player->y - darw->map_y) * darw->delta_dist_y;
	}
	else
	{
		darw->step_y = 1;
		darw->side_dist_y = (darw->map_y + 1.0 - elem->player->y) * darw->delta_dist_y;
	}
}

int	performing_dda(t_draw *draw, t_elements *elem)
{
	int	no_wall;
	int	side;

	no_wall  = 0;
	while (!no_wall)
	{
		if (draw->side_dist_x < draw->side_dist_y)
		{
			draw->side_dist_x += draw->delta_dist_x;
			draw->map_x += draw->step_x;
			side = 0;
		}
		else
		{
			draw->side_dist_y += draw->delta_dist_y;
			draw->map_y += draw->step_y;
			side = 1;
		}
		if (elem->map->map[draw->map_y][draw->map_x] == '1' || elem->map->map[draw->map_y][draw->map_x] == 'D')
		{
			if (elem->map->map[draw->map_y][draw->map_x] == 'D')
				draw->door = 1;
			else
				draw->door = 0;
			no_wall = 1;
		}
		if (elem->map->map[draw->map_y][draw->map_x] == '1')
			no_wall = 1;
	}
	return (side);
}

t_texture	*get_texture(t_elements *elem, t_draw *draw)
{
	if(draw->door == 1)
	{
		return (&elem->textures[4]);
	}
	if (draw->side == 0) // Hit a vertical wall (East or West)
	{
		if (draw->ray_dir_x > 0)
			return (&elem->textures[0]);
		else
			return (&elem->textures[1]);
	}
	else // Hit a horizontal wall (North or South)
	{
		if (draw->ray_dir_y > 0)
			return (&elem->textures[2]);
		else
			return (&elem->textures[3]);
	}
}

long get_texture_pixel(t_texture *tex, int x, int y)
{
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0); // prevent out-of-bounds access

	int pixels_per_line = tex->line_len / 4; // since each pixel is 4 bytes
	int color = tex->addr[y * pixels_per_line + x];

	return (color & 0xFFFFFF); // remove alpha if present
}




long get_color(t_elements *elem, t_draw draw, int y)
{
	t_texture	*textu;
	double		wallx;
	int			tex_x;
	int			tex_y;
	int			h;

	textu = get_texture(elem, &draw);
	if (draw.side == 0)
		wallx = elem->player->y + draw.dist_to_wall * draw.ray_dir_y;
	else
		wallx = elem->player->x + draw.dist_to_wall * draw.ray_dir_x;
	wallx -= floor(wallx); // keep only fractional part
	tex_x = (int)(wallx * textu->width);
	if ((draw.side == 0 && draw.ray_dir_x > 0) || (draw.side == 1 && draw.ray_dir_y < 0))
		tex_x = textu->width - tex_x - 1;
	h = y * 256 - screen_height * 128 + draw.wall_height * 128;
	tex_y = ((h * textu->height) / draw.wall_height) / 256;

	return (get_texture_pixel(textu, tex_x, tex_y));
}

void	drawing(t_elements *elem, double dist, int i, t_draw draw)
{
	int		wall_top;
	int		wall_bottom;
	int		y;
	long	color;

	draw.wall_height = (int)(screen_height / dist);
	wall_top = (screen_height / 2) - (draw.wall_height / 2);
	wall_bottom = (screen_height / 2) + (draw.wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > screen_height)
		wall_bottom = screen_height;
	y = wall_top;
	while (y < wall_bottom)
	{
		color = get_color(elem, draw, y);
		put_pixel_to_image(elem, i, y, color);
		y++;
	}
}

void	start_3d_view(t_elements *elem)
{
	int		i;
	// double	dist;
	t_draw	draw;

	i = 0;
	draw.start_angle = elem->player->angle - (fov / 2.0);
	draw.step_angle = fov / screen_width;
	while (i < screen_width)
	{
		initalize_draw_elems(&draw, i, elem);
		draw.side = performing_dda(&draw, elem);
		double dist_for_height;
		double dist_for_tex;
		if (!draw.side)
			dist_for_tex = (draw.map_x - elem->player->x + (1 - draw.step_x) / 2.0) / draw.ray_dir_x;
		else
			dist_for_tex = (draw.map_y - elem->player->y + (1 - draw.step_y) / 2.0) / draw.ray_dir_y;
		dist_for_height = dist_for_tex * cos(draw.ray_angle - elem->player->angle);

		draw.dist_to_wall = dist_for_tex;
		drawing(elem, dist_for_height, i, draw);
		// drawing(elem, dist, i, draw);
		i++;
	}
}

void	render(t_elements *elem)
{
	int ceiling_color = (elem->c->a << 16) | (elem->c->b << 8) | elem->c->c;
	int floor_color = (elem->f->a << 16) | (elem->f->b << 8) | elem->f->c;

	int y = 0;
	while (y < screen_height)
	{
		int color = (y < screen_height / 2) ? ceiling_color : floor_color;
		int x = 0;
		while (x < screen_width)
		{
			put_pixel_to_image(elem, x, y, color);
			x++;
		}
		y++;
	}
	start_3d_view(elem);
	draw_mini_map(elem);
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
	elem->textures[4].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/door.xpm", &elem->textures[4].width, &elem->textures[4].height);

	while (i < 5)
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
	render(elem);
}
