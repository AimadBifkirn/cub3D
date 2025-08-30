/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:52:33 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/18 12:03:15 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_free(double x, double y, char **map)
{
	double	player_raduis;

	player_raduis = 0.4;
	if (map[(int)(y - player_raduis)][(int)(x - player_raduis)] == '1' ||
		map[(int)(y - player_raduis)][(int)(x + player_raduis)] == '1' ||
		map[(int)(y + player_raduis)][(int)(x - player_raduis)] == '1' ||
		map[(int)(y + player_raduis)][(int)(x + player_raduis)] == '1' ||
		map[(int)(y - player_raduis)][(int)(x - player_raduis)] == 'D' ||
		map[(int)(y - player_raduis)][(int)(x + player_raduis)] == 'D' ||
		map[(int)(y + player_raduis)][(int)(x - player_raduis)] == 'D' ||
		map[(int)(y + player_raduis)][(int)(x + player_raduis)] == 'D')
		return (0);
	return (1);
}

void	move_forward(t_elements *elem)
{
	double	new_x;
	double	new_y;

	new_x = elem->player->x + cos(elem->player->angle) * MOVE_SPEED;
	new_y = elem->player->y + sin(elem->player->angle) * MOVE_SPEED;
	if (is_free(new_x, elem->player->y, elem->map->map))
		elem->player->x = new_x;
	if (is_free(elem->player->x, new_y, elem->map->map))
		elem->player->y = new_y;
}

void	move_backward(t_elements *elem)
{
	double	new_x;
	double	new_y;

	new_x = elem->player->x - cos(elem->player->angle) * MOVE_SPEED;
	new_y = elem->player->y - sin(elem->player->angle) * MOVE_SPEED;
	if (is_free(new_x, elem->player->y, elem->map->map))
		elem->player->x = new_x;
	if (is_free(elem->player->x, new_y, elem->map->map))
		elem->player->y = new_y;
}

void	move_left(t_elements *elem)
{
	double	new_x;
	double	new_y;
	double	angle;

	angle = elem->player->angle - PI / 2;
	new_x = elem->player->x + cos(angle) * MOVE_SPEED;
	new_y = elem->player->y + sin(angle) * MOVE_SPEED;
	if (is_free(new_x, elem->player->y, elem->map->map))
		elem->player->x = new_x;
	if (is_free(elem->player->x, new_y, elem->map->map))
		elem->player->y = new_y;
}

void	move_right(t_elements *elem)
{
	double	new_x;
	double	new_y;
	double	angle;

	angle = elem->player->angle + PI / 2;
	new_x = elem->player->x + cos(angle) * MOVE_SPEED;
	new_y = elem->player->y + sin(angle) * MOVE_SPEED;
	if (is_free(new_x, elem->player->y, elem->map->map))
		elem->player->x = new_x;
	if (is_free(elem->player->x, new_y, elem->map->map))
		elem->player->y = new_y;
}
