/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:26:41 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/29 12:06:17 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


// void check_surronded(t_elements *element)
// {
//     int i;
//     int check[4];
//     int j;
//     char **map = element->map->map;
//     char map2 [2][element->map->colomns];
//     char map3 [2][element->map->rows];

//     i = 0;
//     ft_bzero(check,4 * sizeof(int));
//     ft_bzero(map2,2 * element->map->colomns * sizeof(char));
//     ft_bzero(map3,2 * element->map->rows * sizeof(char));
//     while (i < element->map->rows)
//     {
//         j = 0;
//         while (j < element->map->colomns)
//         {
//             if (map[i][j] == ' ')
//             {
//                 // check UP
//                 if (!map2[0][i] && map[i + 1] && map[i + 1][j] != ' ' && map[i + 1][j] != '1')
//                 {
                    
//                     ft_error_el("Map not surrounded by walls (down)");
//                 }
//                 else if (map[i + 1] && map[i + 1][j] == '1')
//                 {
//                     map2[0][i] = 1;
//                 }
//                 // check LEFT
//                 if (!map3[0][j] && j > 0 && map[i][j - 1] != ' ' && map[i][j - 1] != '1')
//                 {
//                     ft_error_el("Map not surrounded by walls (left)");
                    
//                 }
//                 else if (j > 0 && map[i ][j - 1] && map[i ][j - 1] == 1)
//                 {
//                     map3[0][j] = 1;
//                 }

//                 // check RIGHT
//                 if (!map3[1][j] && map[i][j] && map[i][j + 1] && map[i][j + 1] != ' ' && map[i][j + 1] != '1')
//                 {
//                     ft_error_el("Map not surrounded by walls (right)");
                    
//                 }
//                 else if (map[i][j + 1] && map[i][j + 1] == '1')
//                 {
//                     map3[1][j] = '1';
//                 }
//             }
//             j++;
//         }
//         i++;
//     }
//     while(i > 0)
//     {
//         i--;
//         j = 0;
//         while(map[i][j])
//         {
//             // check DOWN
//             if (map[i][j] == ' ')
//             {
//                 if (!map2[1][i] && i > 0 && map[i - 1][j] != ' ' && map[i - 1][j] != '1')
//                 {
//                     printf("---> %s\n", map[i]);
//                     printf("---> %s\n", map[i - 1]);
//                     ft_error_el("Map not surrounded by walls (up)");
//                 }
//                 else if (i > 0 && map[i - 1][j] == '1')
//                 {
//                     map2[1][i] = 1;
//                 }
//             }
//             j++;
//         }
//     }
// }


void check_surronded(t_elements *element)
{
    int i;
    int check[4];
    int j;
    char **map = element->map->map;
    char map2 [2][element->map->colomns];
    char map3 [2][element->map->rows];

    i = 0;
    ft_bzero(check,4 * sizeof(int));
    ft_bzero(map2,2 * (element->map->colomns + 1) * sizeof(char));
    ft_bzero(map3,2 * (element->map->rows + 1) * sizeof(char));
    while (i < element->map->rows)
    {
        j = 0;
        while (j < element->map->colomns)
        {
            if (map[i][j] == ' ')
            {
                // check UP
                if (map[i + 1] && map[i + 1][j] && map[i + 1][j] != ' ' && map[i + 1][j] != '1')
                {
                    printf ("->%s\n",map[i]);
                    printf ("->%d\n",i);
                    ft_error_el("Map not surrounded by walls (down)");
                }
                // check LEFT
                if (j > 0 && map[i][j - 1] != ' ' && map[i][j - 1] != '1')
                {
                    ft_error_el("Map not surrounded by walls (left)");
                    
                }

                // check RIGHT
                if ( j < element->map->colomns && map[i][j + 1] && map[i][j + 1] != ' ' && map[i][j + 1] != '1')
                {
                    ft_error_el("Map not surrounded by walls (right)");
                    
                }
            }
            j++;
        }
        i++;
    }
}

void    cheack_map(void)
{
    t_elements *element;

    element = getter();
    check_surronded(element);
}