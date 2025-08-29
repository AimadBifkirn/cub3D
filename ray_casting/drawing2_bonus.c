/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:31:04 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int	color_val(t_texture *tex, int *first_pixel_y, int *last_pixel_y)
{
	int	color;
	int	y;
	int	x;

	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			color = get_texture_pixel(tex, x, y);
			if ((color & 0x00FFFFFF) != 0x00000000)
			{
				if (y < *first_pixel_y)
					*first_pixel_y = y;
				if (y > *last_pixel_y)
					*last_pixel_y = y;
			}
			x++;
		}
		y++;
	}
	return (color);
}

void	put_it(t_elements *elem, t_texture *tex, int size, int *data)
{
	int	y;
	int	x;
	int	color;
	int	draw_x;
	int	draw_y;

	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
		{
			color = get_texture_pixel(tex, (x * tex->width) / size, data[0]
					+ ((y * data[1]) / size));
			if ((color & 0x00FFFFFF) == 0x00000000)
				continue ;
			draw_x = (int)SCREEN_WIDTH / 2 - size / 2 + x;
			draw_y = (int)SCREEN_HEIGHT - 100 - size / 2 + y;
			if (draw_x >= 0 && draw_x < SCREEN_WIDTH && draw_y >= 0
				&& draw_y < SCREEN_HEIGHT)
				put_pixel_to_image(elem, draw_x, draw_y, color);
		}
	}
}
