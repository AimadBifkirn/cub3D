/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:40:30 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/18 15:27:10 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_texture	*get_texture(t_elements *elem, t_draw *draw)
{
	if (draw->door == 1)
	{
		return (&elem->textures[4]);
	}
	if (draw->side == 0)
	{
		if (draw->ray_dir_x > 0)
			return (&elem->textures[0]);
		else
			return (&elem->textures[1]);
	}
	else
	{
		if (draw->ray_dir_y > 0)
			return (&elem->textures[2]);
		else
			return (&elem->textures[3]);
	}
}

void	init_img_ptr(t_elements *elem, t_texture *textu, char *file)
{
	textu->img_ptr = mlx_xpm_file_to_image(elem->mlx, file, \
	&textu->width, &textu->height);
}

void	load_gun_textu(t_elements *elem)
{
	init_img_ptr(elem, &elem->enemy->textures[0], "textures/enemy/frame07.xpm");
	init_img_ptr(elem, &elem->enemy->textures[1], "textures/enemy/frame08.xpm");
	init_img_ptr(elem, &elem->enemy->textures[2], "textures/enemy/frame09.xpm");
	init_img_ptr(elem, &elem->enemy->textures[3], "textures/enemy/frame10.xpm");
	init_img_ptr(elem, &elem->enemy->textures[4], "textures/enemy/frame11.xpm");
	init_img_ptr(elem, &elem->enemy->textures[5], "textures/enemy/frame12.xpm");
	init_img_ptr(elem, &elem->enemy->textures[6], "textures/enemy/frame13.xpm");
	init_img_ptr(elem, &elem->enemy->textures[7], "textures/enemy/frame14.xpm");
	init_img_ptr(elem, &elem->enemy->textures[8], "textures/enemy/frame15.xpm");
	init_img_ptr(elem, &elem->enemy->textures[9], "textures/enemy/frame16.xpm");
}

void	check_loading(t_elements *elem)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (!elem->textures[i].img_ptr)
			error_textures("(walls/door)", i);
		elem->textures[i].addr = (int *)mlx_get_data_addr \
		(elem->textures[i].img_ptr, &elem->textures[i].bpp, \
		&elem->textures[i].line_len, &elem->textures[i].endian);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (!elem->enemy->textures[i].img_ptr)
			error_textures("(gun)", i);
		elem->enemy->textures[i].addr = (int *)mlx_get_data_addr \
		(elem->enemy->textures[i].img_ptr, &elem->enemy->textures[i].bpp, \
		&elem->enemy->textures[i].line_len, &elem->enemy->textures[i].endian);
		i++;
	}
}

void	load_textures(t_elements *elem)
{
	elem->textures[0].img_ptr = mlx_xpm_file_to_image(elem->mlx, \
	"textures/wall_1.xpm", &elem->textures[0].width, &elem->textures[0].height);
	elem->textures[1].img_ptr = mlx_xpm_file_to_image(elem->mlx, \
	"textures/wall_2.xpm", &elem->textures[1].width, &elem->textures[1].height);
	elem->textures[2].img_ptr = mlx_xpm_file_to_image(elem->mlx, \
	"textures/wall_3.xpm", &elem->textures[2].width, &elem->textures[2].height);
	elem->textures[3].img_ptr = mlx_xpm_file_to_image(elem->mlx, \
	"textures/wall_4.xpm", &elem->textures[3].width, &elem->textures[3].height);
	elem->textures[4].img_ptr = mlx_xpm_file_to_image(elem->mlx, \
	"textures/door.xpm", &elem->textures[4].width, &elem->textures[4].height);
	load_gun_textu(elem);
	check_loading(elem);
}
