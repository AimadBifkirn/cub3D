/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:40:21 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	helper_work(t_elements *arg)
{
	close_doors (arg);
	render (arg);
	arg->j++;
	if (arg->j > 9)
	{
		arg->j = 0;
		arg->shooting = 0;
	}
}

int	loop_work(void *elem)
{
	t_elements	*arg;

	arg = elem;
	if (arg->keys.left)
		rotate_left(arg);
	if (arg->keys.right)
		rotate_right(arg);
	if (arg->keys.w)
		move_forward(arg);
	if (arg->keys.s)
		move_backward(arg);
	if (arg->keys.a)
		move_left(arg);
	if (arg->keys.d)
		move_right(arg);
	if (arg->shooting)
		helper_work(arg);
	else
	{
		close_doors(arg);
		render(arg);
	}
	return (0);
}

int	main(int ac, char **argv)
{
	t_elements	*element;

	element = getter();
	parcing_mn(ac, argv);
	put_doors(element);
	element->mlx = mlx_init();
	element->wind = mlx_new_window(element->mlx, SCREEN_WIDTH, \
	SCREEN_HEIGHT, "Cube3D");
	element->img = mlx_new_image(element->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	element->addr = mlx_get_data_addr(element->img, \
	&element->bits_per_px, &element->line_len, &element->endian);
	ray_casting(element);
	mlx_hook(element->wind, 6, 1L << 6, mouse_move_handler, element);
	mlx_hook(element->wind, 2, 1L << 0, event_handeler, element);
	mlx_hook(element->wind, 3, 1L << 1, key_release, element);
	mlx_hook(element->wind, 4, 1L << 2, check_button, element);
	mlx_loop_hook(element->mlx, loop_work, element);
	mlx_hook(element->wind, 17, 0, close_window, NULL);
	mlx_loop(element->mlx);
	return (0);
}
