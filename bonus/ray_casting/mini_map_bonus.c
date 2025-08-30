/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:29:02 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	draw_player(t_elements *elem)
{
	int	size;
	int	mini_p_x;
	int	mini_p_y;
	int	y;
	int	x;

	size = 3;
	mini_p_x = MINIMAP_SIZE / 2;
	mini_p_y = MINIMAP_SIZE / 2;
	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			put_pixel_to_image(elem, mini_p_x \
			+ (x - 0.5), mini_p_y + (y - 0.5), 0x0000FF);
			x++;
		}
		y++;
	}
}

int	check_bounds(t_elements *elem, double ray_x, double ray_y)
{
	double	m_s;

	m_s = MOVE_SPEED;
	if (elem->map->map[(int)ray_y][(int)ray_x] == '1')
		return (1);
	if (elem->map->map[(int)(ray_y - m_s)][(int)(ray_x - m_s)] == '1')
		return (1);
	if (elem->map->map[(int)(ray_y + m_s)][(int)(ray_x + m_s)] == '1')
		return (1);
	if (elem->map->map[(int)(ray_y + m_s)][(int)(ray_x - m_s)] == '1')
		return (1);
	if (elem->map->map[(int)(ray_y - m_s)][(int)(ray_x + m_s)] == '1')
		return (1);
	if (elem->map->map[(int)ray_y][(int)ray_x] == 'D')
		return (1);
	if (elem->map->map[(int)(ray_y - m_s)][(int)(ray_x - m_s)] == 'D')
		return (1);
	if (elem->map->map[(int)(ray_y + m_s)][(int)(ray_x + m_s)] == 'D')
		return (1);
	if (elem->map->map[(int)(ray_y + m_s)][(int)(ray_x - m_s)] == 'D')
		return (1);
	if (elem->map->map[(int)(ray_y - m_s)][(int)(ray_x + m_s)] == 'D')
		return (1);
	return (0);
}

void	cast_m_rays_helper(double angle, t_elements *elem)
{
	double	ray_x;
	double	ray_y;
	int		pixel_x;
	int		pixel_y;

	ray_x = elem->player->x;
	ray_y = elem->player->y;
	while (1)
	{
		ray_x += cos(angle) * MOVE_SPEED;
		ray_y += sin(angle) * MOVE_SPEED;
		if (check_bounds(elem, ray_x, ray_y))
			break ;
		pixel_x = (ray_x - elem->player->x) \
		* MINIMAP_TILE_SIZE + MINIMAP_SIZE / 2;
		pixel_y = (ray_y - elem->player->y) \
		* MINIMAP_TILE_SIZE + MINIMAP_SIZE / 2;
		if (pixel_x < 0 || pixel_y < 0 \
		|| pixel_x >= MINIMAP_SIZE || pixel_y >= MINIMAP_SIZE)
			break ;
		put_pixel_to_image(elem, pixel_x, pixel_y, 0x00FFFF);
	}
}

void	cast_multiple_rays(t_elements *elem)
{
	double	start_angle;
	double	step_angle;
	double	angle;
	int		i;

	start_angle = elem->player->angle - FOV / 2;
	step_angle = FOV / 10;
	i = 0;
	while (i < 10)
	{
		angle = start_angle + (i * step_angle);
		cast_m_rays_helper(angle, elem);
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
