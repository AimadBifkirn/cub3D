/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:55:04 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/18 12:13:47 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	close_window(void *param)
{
	(void)param;
	ft_free_all();
	exit (0);
	return (0);
}

void	rotate_left(t_elements *elem)
{
	elem->player->angle -= ROT_SPEED;
	if (elem->player->angle < 0)
		elem->player->angle += 2 * PI;
}

void	rotate_right(t_elements *elem)
{
	elem->player->angle += ROT_SPEED;
	if (elem->player->angle > 2 * PI)
		elem->player->angle -= 2 * PI;
}

int	mouse_move_handler(int x, int y, t_elements *elem)
{
	static int	last_x = -1;
	int			delta_x;
	double		sensitivity;

	(void)y;
	if (last_x == -1)
		last_x = x;
	delta_x = x - last_x;
	last_x = x;
	sensitivity = 0.001;
	elem->player->angle += delta_x * sensitivity;
	if (elem->player->angle < 0)
		elem->player->angle += 2 * PI;
	else if (elem->player->angle > 2 * PI)
		elem->player->angle -= 2 * PI;
	return (0);
}
