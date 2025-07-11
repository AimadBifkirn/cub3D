/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:40:21 by zmounji           #+#    #+#             */
/*   Updated: 2025/07/06 15:04:36 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_elements *getter(void)
{
    static t_elements elements;
    if (elements.map == NULL)
    {
        elements.map = malloc(sizeof(t_map));
        if (!elements.map)
            return (NULL);
        ft_bzero(elements.map, sizeof(t_map));
    }
    return (&elements);
}

void    print_map(t_elements *element)
{
    int i;

    i = 0;
    printf("start\n");
    while(i < element->map->rows)
    {
        printf("%s\n", element->map->map[i]);
        i++;
    }
    printf("end\n");
}


int main(int ac, char ** argv)
{
    t_elements  *element;

    element = getter();
    parcing_mn(ac, argv);
    print_map(element);
    // deb_map();
    element->mlx = mlx_init();
    element->wind = mlx_new_window(element->mlx, 800, 600, "Cube3D");
    ray_casting(&element);
    mlx_loop(element->mlx);
    return (0);
}
