/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:47:47 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 15:29:48 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	destroy_win_des(t_elements *element)
{
	if (element->wind)
		mlx_destroy_window(element->mlx, element->wind);
	if (element->mlx)
	{
		mlx_destroy_display(element->mlx);
		free (element->mlx);
	}
}
