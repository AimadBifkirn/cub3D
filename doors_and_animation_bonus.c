/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_and_animation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:45:45 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 10:56:41 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	put_enemy(t_elements *element)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = element->map->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' && map[i][j + 1] == '0' \
			&& (j - 1) > 0 && map[i][j - 1] == '0')
			{
				element->enemy = ft_malloc(sizeof(t_enemy));
				if (!element->enemy)
					ft_error_el("ERROR \n");
				element->enemy->x = j;
				element->enemy->y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	replace_with_doors(t_elements *element, int i, int j, char **map)
{
	if (map[i][j] == '0')
	{
		if (map[i + 1] && map[i + 1][j] == '1' && ((i - 1) >= 0) \
		&& map[i - 1][j] == '1' && i != 0 && i != element->map->colomns \
		&& j != 0 && j != element->map->colomns && map[i][j + 1] != '1' \
		&& (j - 1) >= 0 && map[i][j - 1] != '1')
			map[i][j] = 'D';
	}
	if (map[i][j] == '0')
	{
		if (((j - 1) >= 0) && map[i][j - 1] == '1' && map[i][j + 1] \
		&& map[i][j + 1] == '1' && i != 0 && i != element->map->colomns \
		&& j != 0 && j != element->map->colomns && map[i + 1] \
		&& map[i + 1][j] != '1' && (i - 1) >= 0 && map[i - 1][j] != '1' )
			map[i][j] = 'D';
	}
}

void	put_doors(t_elements *element)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = element->map->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			replace_with_doors(element, i, j, map);
			j++;
		}
		i++;
	}
}

void	close_doors(t_elements *elem)
{
	char	**map;
	int		dx;
	int		dy;
	int		back_x;
	int		back_y;

	map = elem->map->map;
	dx = (int)round(cos(elem->player->angle));
	dy = (int)round(sin(elem->player->angle));
	back_x = (int)(elem->player->x) - 2 * dx;
	back_y = (int)(elem->player->y) - 2 * dy;
	if (back_y >= 0 && back_y < elem->map->rows && (int)(elem->player->x) >= 0 \
	&& (int)(elem->player->x) < elem->map->colomns \
	&& map[back_y][(int)(elem->player->x)] == 'd' \
	&& (int)(elem->player->y) != back_y)
		map[back_y][(int)(elem->player->x)] = 'D';
	if (back_x >= 0 && back_x < elem->map->colomns \
	&& (int)(elem->player->y) >= 0 \
	&& (int)(elem->player->y) < elem->map->rows \
	&& map[(int)(elem->player->y)][back_x] == 'd' \
	&& (int)(elem->player->x) != back_x)
		map[(int)(elem->player->y)][back_x] = 'D';
}
