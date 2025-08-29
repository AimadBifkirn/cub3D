/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:48:21 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	oupen_door(t_elements *elem)
{
	char	**map;
	int		dx;
	int		dy;
	int		tx;
	int		ty;

	map = elem->map->map;
	dx = (int)round(cos(elem->player->angle));
	dy = (int)round(sin(elem->player->angle));
	tx = (int)(elem->player->x) + dx;
	ty = (int)(elem->player->y) + dy;
	if (ty >= 0 && ty < elem->map->rows && tx >= 0 && tx < elem->map->colomns)
	{
		if (map[ty][tx] == 'D')
		{
			map[ty][tx] = 'd';
		}
	}
}

void	shooting(t_elements *elem)
{
	elem->shooting = 1;
}

int	key_release(int code, t_elements *elem)
{
	if (code == 65361)
		elem->keys.left = 0;
	if (code == 65363)
		elem->keys.right = 0;
	if (code == 'w')
		elem->keys.w = 0;
	if (code == 's')
		elem->keys.s = 0;
	if (code == 'a')
		elem->keys.a = 0;
	if (code == 'd')
		elem->keys.d = 0;
	return (0);
}

int	event_handeler(int code, t_elements *elem)
{
	if (code == 65361)
		elem->keys.left = 1;
	if (code == 65363)
		elem->keys.right = 1;
	if (code == 'w')
		elem->keys.w = 1;
	if (code == 's')
		elem->keys.s = 1;
	if (code == 'a')
		elem->keys.a = 1;
	if (code == 'd')
		elem->keys.d = 1;
	if (code == 'o')
		oupen_door(elem);
	if (code == 65307)
		ft_esc("ESC\n");
	return (0);
}

int	check_button(int code, int x, int y, void *element)
{
	t_elements	*elem;

	(void) x;
	(void) y;
	elem = (t_elements *) element;
	if (code == 1)
		shooting(elem);
	return (0);
}
