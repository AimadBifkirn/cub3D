/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:31:04 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	draw_pistol(t_elements *elem, t_texture *tex, int size)
{
	int	first_pixel_y;
	int	last_pixel_y;
	int	color;
	int	cropped_height;
	int	data[2];

	first_pixel_y = tex->height;
	last_pixel_y = 0;
	color = color_val(tex, &first_pixel_y, &last_pixel_y);
	cropped_height = last_pixel_y - first_pixel_y + 1;
	data[0] = first_pixel_y;
	data[1] = cropped_height;
	put_it(elem, tex, size, data);
}

void	step_and_side_dist(t_draw *draw, t_elements *elem)
{
	if (draw->ray_dir_x < 0)
	{
		draw->step_x = -1;
		draw->side_dist_x = (elem->player->x - draw->map_x)
			* draw->delta_dist_x;
	}
	else
	{
		draw->step_x = 1;
		draw->side_dist_x = (draw->map_x + 1.0 - elem->player->x)
			* draw->delta_dist_x;
	}
	if (draw->ray_dir_y < 0)
	{
		draw->step_y = -1;
		draw->side_dist_y = (elem->player->y - draw->map_y)
			* draw->delta_dist_y;
	}
	else
	{
		draw->step_y = 1;
		draw->side_dist_y = (draw->map_y + 1.0 - elem->player->y)
			* draw->delta_dist_y;
	}
}

void	initalize_draw_elems(t_draw *draw, int i, t_elements *elem)
{
	draw->ray_angle = draw->start_angle + i * draw->step_angle;
	draw->ray_dir_x = cos(draw->ray_angle);
	draw->ray_dir_y = sin(draw->ray_angle);
	draw->delta_dist_x = fabs(1 / draw->ray_dir_x);
	draw->delta_dist_y = fabs(1 / draw->ray_dir_y);
	draw->map_x = (int)elem->player->x;
	draw->map_y = (int)elem->player->y;
	step_and_side_dist(draw, elem);
}

void	drawing(t_elements *elem, double dist, int i, t_draw draw)
{
	int		wall_top;
	int		wall_bottom;
	int		y;
	long	color;

	draw.wall_height = (int)(SCREEN_HEIGHT / dist);
	wall_top = (SCREEN_HEIGHT / 2) - (draw.wall_height / 2);
	wall_bottom = (SCREEN_HEIGHT / 2) + (draw.wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > SCREEN_HEIGHT)
		wall_bottom = SCREEN_HEIGHT;
	y = wall_top;
	while (y < wall_bottom)
	{
		color = get_color(elem, draw, y);
		put_pixel_to_image(elem, i, y, color);
		y++;
	}
}
