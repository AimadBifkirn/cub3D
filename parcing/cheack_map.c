/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:26:41 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/20 21:12:14 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	check_space(t_elements *element, int i, int j)
{
	char	**map;

	map = element->map->map;
	if (map[i + 1] && map[i + 1][j] && map[i + 1][j] != ' ' \
	&& map[i + 1][j] != '1')
		ft_error_el("Map not surrounded by walls (down)");
	if (i > 0 && map[i - 1][j] && map[i - 1][j] != ' ' \
	&& map[i - 1][j] != '1')
		ft_error_el("Map not surrounded by walls (down)");
	if (j > 0 && map[i][j - 1] != ' ' && map[i][j - 1] != '1')
		ft_error_el("Map not surrounded by walls (left)");
	if (j < element->map->colomns && map[i][j + 1] \
	&& map[i][j + 1] != ' ' && map[i][j + 1] != '1')
		ft_error_el("Map not surrounded by walls (right)");
}

void	check_surronded(t_elements *element)
{
	int		i;
	int		j;
	char	**map;

	map = element->map->map;
	i = -1;
	while (++i < element->map->rows)
	{
		j = -1;
		while (++j < element->map->colomns)
		{
			if (map[i][j] == ' ')
				check_space(element, i, j);
			if (map[i][j] == '0')
			{
				if (((i - 1) < 0) || !map[i][j + 1] || j == 0)
				{
					printf ("->%s\n", map[i]);
					printf ("->%d\n", i);
					ft_error_el("Map not surrounded by walls (down)");
				}
			}
		}
	}
}

void	valid_character(t_elements *elem)
{
	char	**map;
	int		i;
	int		j;

	map = elem->map->map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ' \
			&& map[i][j] != 'N' && map[i][j] != 'S' \
			&& map[i][j] != 'E' && map[i][j] != 'W')
				ft_error_el("error\n");
			if (map[i][j] == 'N' || map[i][j] == 'S' \
			|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (elem->player)
					ft_error_el("Just one player\n");
				elem->player = ft_malloc(sizeof(t_player));
			}
		}
	}
}

void	cheack_map(void)
{
	t_elements	*element;

	element = getter();
	check_surronded(element);
	valid_character(element);
	if (!element->player)
		ft_error_el("No player here \n");
	if (!element->enemy)
		element->enemy = ft_malloc(sizeof(t_enemy));
}
