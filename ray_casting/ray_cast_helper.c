/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:30:43 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 17:58:31 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	get_player_direction(t_elements *elem)
{
	int	p_x;
	int	p_y;

	p_x = (int)(elem->player->x);
	p_y = (int)(elem->player->y);
	if (elem->map->map[p_y][p_x] == 'N')
		elem->player->angle = -(PI / 2);
	else if (elem->map->map[p_y][p_x] == 'S')
		elem->player->angle = (PI / 2);
	else if (elem->map->map[p_y][p_x] == 'E')
		elem->player->angle = 0;
	else if (elem->map->map[p_y][p_x] == 'W')
		elem->player->angle = PI;
}

void	put_pixel_to_image(t_elements *elem, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = elem->addr + (y * elem->line_len + x * (elem->bits_per_px / 8));
	*(unsigned int *)dst = color;
}

long	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	pixels_per_line;
	int	color;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixels_per_line = tex->line_len / 4;
	color = tex->addr[y * pixels_per_line + x];
	return (color & 0xFFFFFF);
}

long	get_color(t_elements *elem, t_draw draw, int y)
{
	t_texture	*textu;
	double		wallx;
	int			tex_x;
	int			tex_y;
	int			h;

	textu = get_texture(elem, &draw);
	if (draw.side == 0)
		wallx = elem->player->y + draw.dist_to_wall * draw.ray_dir_y;
	else
		wallx = elem->player->x + draw.dist_to_wall * draw.ray_dir_x;
	wallx -= (int)(wallx);
	tex_x = (int)(wallx * textu->width);
	if ((draw.side == 0 && draw.ray_dir_x > 0) \
	|| (draw.side == 1 && draw.ray_dir_y < 0))
		tex_x = textu->width - tex_x - 1;
	h = y * 256 - SCREEN_HEIGHT * 128 + draw.wall_height * 128;
	tex_y = ((h * textu->height) / draw.wall_height) / 256;
	return (get_texture_pixel(textu, tex_x, tex_y));
}

void	error_textures(char *str, int i)
{
	printf ("Failed to load texture %s n : %d\n", str, i);
	ft_free_all ();
	exit (1);
}
