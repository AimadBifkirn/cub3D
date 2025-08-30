/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_helper_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:18:51 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	put_pixels(t_elements *elem, int x, int y)
{
	int	pixel_y;
	int	pixel_x;
	int	color;
	int	draw_x;
	int	draw_y;

	draw_x = ((x - elem->player->x) * MINIMAP_TILE_SIZE) + MINIMAP_SIZE / 2;
	draw_y = ((y - elem->player->y) * MINIMAP_TILE_SIZE) + MINIMAP_SIZE / 2;
	if (elem->map->map[y][x] == '1')
		color = 0xCCCCCC;
	else if (elem->map->map[y][x] == 'D')
		color = 0xAAAAAA;
	else
		color = 0x333333;
	pixel_y = 0;
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

	y = 0;
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

void	draw_map(t_elements *elem)
{
	t_m_map	mini_m;
	int		y;
	int		x;

	mini_m = init_elements(elem);
	y = mini_m.start_y;
	while (y < mini_m.end_y && y < 80)
	{
		x = mini_m.start_x;
		while (x < mini_m.end_x && x < 80)
		{
			put_pixels(elem, x, y);
			x++;
		}
		y++;
	}
}
