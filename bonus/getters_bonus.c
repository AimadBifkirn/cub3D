/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:41:48 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

t_elements	*getter(void)
{
	static t_elements	elements;

	if (elements.map == NULL)
	{
		elements.map = ft_malloc(sizeof(t_map));
		if (!elements.map)
			return (NULL);
		ft_bzero(elements.map, sizeof(t_map));
	}
	return (&elements);
}

t_draw	*getter_draw(void)
{
	static t_draw	draw;

	return (&draw);
}

t_collecter	**getter_garbage(void)
{
	static t_collecter	*garbage;

	return (&garbage);
}
