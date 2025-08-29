/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:53:01 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

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

int	performing_dda(t_draw *draw, t_elements *elem)
{
	int		side;
	char	**map;

	map = elem->map->map;
	while (1)
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
		if (map[draw->map_y][draw->map_x] == '1' \
		|| map[draw->map_y][draw->map_x] == 'D')
		{
			draw->door = (map[draw->map_y][draw->map_x] == 'D');
			return (side);
		}
	}
}

void	start_3d_view(t_elements *elem)
{
	int		i;
	t_draw	draw;
	double	dist_for_height;
	double	dist_for_tex;

	i = 0;
	draw.start_angle = elem->player->angle - (FOV / 2.0);
	draw.step_angle = FOV / SCREEN_WIDTH;
	while (i < SCREEN_WIDTH)
	{
		initalize_draw_elems(&draw, i, elem);
		draw.side = performing_dda(&draw, elem);
		if (!draw.side)
			dist_for_tex = (draw.map_x - elem->player->x \
			+ (1 - draw.step_x) / 2.0) / draw.ray_dir_x;
		else
			dist_for_tex = (draw.map_y - elem->player->y \
			+ (1 - draw.step_y) / 2.0) / draw.ray_dir_y;
		dist_for_height = dist_for_tex \
		* cos(draw.ray_angle - elem->player->angle);
		draw.dist_to_wall = dist_for_tex;
		drawing(elem, dist_for_height, i, draw);
		i++;
	}
	draw_pistol(elem, &elem->enemy->textures[elem->j], 400);
}

void	render(t_elements *elem)
{
	int	ceiling_color;
	int	floor_color;
	int	color;
	int	y;
	int	x;

	ceiling_color = (elem->c->a << 16) | (elem->c->b << 8) | elem->c->c;
	floor_color = (elem->f->a << 16) | (elem->f->b << 8) | elem->f->c;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < SCREEN_HEIGHT / 2)
			color = ceiling_color;
		else
			color = floor_color;
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			put_pixel_to_image(elem, x, y, color);
		}
		y++;
	}
	start_3d_view(elem);
	draw_mini_map(elem);
	mlx_put_image_to_window(elem->mlx, elem->wind, elem->img, 0, 0);
}

void	ray_casting(t_elements *elem)
{
	if (!elem->player)
		elem->player = ft_malloc (sizeof(t_player));
	get_player_pos(elem);
	load_textures(elem);
	render(elem);
}
