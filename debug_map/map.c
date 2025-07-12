/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:16:13 by zmounji           #+#    #+#             */
/*   Updated: 2025/07/12 17:59:21 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


void    check_angle(char c)
{
    t_elements  *element;

    element = getter();
    if(c == 'N')
        element->player->angle = 90;
    if(c == 'S')
        element->player->angle = 270;
    if(c == 'O')
        element->player->angle = 180;
    if(c == 'E')
        element->player->angle = 0;
}

void    set_up_player(void)
{
    t_elements  *element;
    char        **map;
    int         i;
    int         j;
    
    element = getter();
    map = element->map->map;
    i = 0;
    if (!map)
        ft_error_el("mrid f krk\n");
    while (i < element->map->rows)
    {
        j = 0;
        while (j < element->map->colomns)
        {
            if (element->map->map[i][j] == 'N' || element->map->map[i][j] == 'S' || element->map->map[i][j] == 'O' || element->map->map[i][j] == 'E')
            {
                if(element->player)
                    ft_error("one player\n");
                element->player = malloc(sizeof(t_player));
                if (!element->player)
                    ft_error_el("mallo\n");
                ft_bzero(element->player, sizeof(t_player));
                element->player->direction = malloc(2);
                if (!element->player->direction)
                    ft_error_el("malloc\n");
                element->player->direction[0] = map[i][j];
                element->player->direction[1] = '\0';
                element->player->x = j;
                element->player->px = ((j * window_py) + (window_py / 2));
                element->player->y = i;
                element->player->py = ((i * window_py) + (window_px / 2));
                check_angle(element->map->map[i][j]);
                element->map->map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    
}

void put_pixel_in_big_image(t_elements *element, int x, int y, int color)
{
    int pixel_offset;
    
    // Check bounds
    if (x < 0 || x >= element->map->colomns * window_px || 
        y < 0 || y >= element->map->rows * window_py)
        return;
    
    // Calculate pixel position in big image
    pixel_offset = (y * element->drawing->line_length) + (x * (element->drawing->bits_per_pixel / 8));
    
    // Set pixel color in big image
    *(unsigned int*)(element->drawing->addr + pixel_offset) = color;
}

void draw_circle_in_big_image(t_elements *element, int center_x, int center_y, int radius, int color)
{
    int x, y;
    int distance_squared;
    
    for (y = center_y - radius; y <= center_y + radius; y++)
    {
        for (x = center_x - radius; x <= center_x + radius; x++)
        {
            int dx = x - center_x;
            int dy = y - center_y;
            distance_squared = (dx * dx) + (dy * dy);
            
            if (distance_squared <= (radius * radius))
                put_pixel_in_big_image(element, x, y, color);
        }
    }
}

void draw_wall_in_big_image(t_elements *element, int start_x, int start_y, int size, int color)
{
    int x, y;
    y = start_y;
    while(y < (start_y + size))
    {
        x = start_x;

        while (x < (start_x + size))
        {
            put_pixel_in_big_image(element, x, y, color);
            x++;
        }
        y++;
    }
}

// void *create_colored_image(t_elements  *element, int width, int height, int color)
// {
//     void    *img;
//     char    *addr;
//     int     bits_per_pixel;
//     int     line_length;
//     int     endian;
//     int     x, y;

//     img = mlx_new_image(element->drawing->mlx, width, height);
//     if (!img)
//         return (NULL);
    
//     addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
//     y = 0;
//     while (y < height)
//     {
//         x = 0;
//         while (x < width)
//         {
//             int pixel_offset = (y * line_length) + (x * (bits_per_pixel / 8));
//             *(unsigned int*)(addr + pixel_offset) = color;
//             x++;
//         }
//         y++;
//     }
    
//     return (img);
// }

// void *create_circle_image(t_elements *element, int size, int color)
// {
//     void    *img;
//     char    *addr;
//     int     bits_per_pixel;
//     int     line_length;
//     int     endian;
//     int     x, y;
//     int     center_x, center_y;
//     int     radius;
//     int     distance_squared;

//     // Create new image
//     img = mlx_new_image(element->drawing->mlx, size, size);
//     if (!img)
//         return (NULL);
    
//     // Get image data address
//     addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
    
//     // Calculate circle parameters
//     center_x = size / 2;
//     center_y = size / 2;
//     radius = (size / 2) - 1; // Slightly smaller than the tile
    
//     // Fill the image with transparent background and yellow circle
//     y = 0;
//     while (y < size)
//     {
//         x = 0;
//         while (x < size)
//         {
//             // Calculate distance from center
//             int dx = x - center_x;
//             int dy = y - center_y;
//             distance_squared = (dx * dx) + (dy * dy);
            
//             // Calculate pixel position in memory
//             int pixel_offset = (y * line_length) + (x * (bits_per_pixel / 8));
            
//             // Draw circle
//             if (distance_squared <= (radius * radius))
//                 *(unsigned int*)(addr + pixel_offset) = color;
//             else
//                 *(unsigned int*)(addr + pixel_offset) = 0x00000000; // Transparent
//             x++;
//         }
//         y++;
//     }
    
//     return (img);
// }

void clear_big_image(t_elements *element, int bg_color)
{
    int total_pixels = (element->map->colomns * window_px) * (element->map->rows * window_py);
    int i;
    
    for (i = 0; i < total_pixels; i++)
    {
        ((unsigned  int *)element->drawing->addr)[i] = bg_color;
    }
}

void    inisialise_dr(void)
{
    t_elements  *element;
    
    element = getter();
    element->drawing = malloc(sizeof(t_draw));
    if (!element->drawing)
        ft_error_el("malloc\n");
    ft_bzero(element->drawing, sizeof(t_draw));
    element->drawing->mlx = mlx_init();
    // element->drawing->player_img = create_circle_image(element, player_raduis, player_color);<----------------------
    // element->drawing->player_img = mlx_xpm_file_to_image(element->drawing->mlx, "texture/player_deb.xpm", &(int){0}, &(int){0});
    // element->drawing->wall_img = mlx_xpm_file_to_image(element->drawing->mlx, "texture/wall_deb.xpm", &(int){0}, &(int){0});
    // element->drawing->wall_img = create_colored_image(element, window_py, window_px, wall_color);<---------------------------
    element->drawing->win = mlx_new_window(element->drawing->mlx, element->map->colomns * window_px, element->map->rows * window_py, "Cub3D");
    element->drawing->big_image = mlx_new_image(element->drawing->mlx, element->map->colomns * window_px, element->map->rows * window_py);
    element->drawing->addr = mlx_get_data_addr(element->drawing->big_image, &element->drawing->bits_per_pixel, &element->drawing->line_length, &element->drawing->endian);
}

void draw_oblique_ray(t_elements *e, double angle)
{
    double x = e->player->px + (player_raduis / 2);
    double y = e->player->py + (player_raduis / 2);
    double step = 0;
    int pixel_offset;

    while (1)
    {
        double ray_x = x + cos(angle) * step;
        double ray_y = y - sin(angle) * step;

        int grid_x = (int)(ray_x / window_px);
        int grid_y = (int)(ray_y / window_py);

        if (grid_y < 0 || grid_x < 0 || grid_y >= e->map->rows || grid_x >= e->map->colomns)
            break;
        if (e->map->map[grid_y][grid_x] == '1')
            break;
        pixel_offset = ((int)ray_y * e->drawing->line_length) + ((int)ray_x * (e->drawing->bits_per_pixel / 8));
        if ((((y - ray_y) < (window_py) ) && ((y - ray_y) > -(window_py) )) && (((x - ray_x) < (window_px) ) && ((x - ray_x) > -(window_px) )))
            *(unsigned int*)(e->drawing->addr + pixel_offset) = 0x00FFFF00;
        else
            *(unsigned int*)(e->drawing->addr + pixel_offset) = 0x00FF0000;
        

        step += 1;
    }
}

int ray_vertical(double x, double y, double angle)
{
    t_elements *e;
    e = getter();
    char    **map;
    int     mapx;
    int     mapy;
    map = e->map->map;
    // if (fmod(angle, (PI / 2)) == 0.0)
    //     return (1);
    double dy = tan(angle);
    double px = x - (e->player->x * window_px);
    double sdy = (1-px)*tan(angle);
    y-=sdy;
    mapx = (int) (x + player_raduis/2)/window_px;
    mapy = (int) (y - player_raduis/2)/window_py;
    if (mapy < 0 || mapy >= e->map->rows || mapx < 0 || mapx >= e->map->colomns)
    {
        printf("heyyyy\n");
        return (1);
    }
    if (map[mapy][mapx] == '1')
        return (1);
    y-=dy;
    mapx = (int) x/window_px;
    mapy = (int) y/window_py;
    if (mapy < 0 || mapy >= e->map->rows || mapx < 0 || mapx >= e->map->colomns)
    {
        return (1);
    }
    if (map[mapy][mapx] == '1')
    {
        // printf("heyyyy\n");
        return (1);
    }
    return(0);
    
}

int ray_horizental(double x, double y, double angle)
{
    t_elements *e;
    e = getter();
    char    **map;
    int     mapx;
    int     mapy;
    map = e->map->map;
    // if (fmod(angle, (PI / 2)) == 0.0)
    //     return (1);
    double dx = 1/tan(angle);
    double py = y - (e->player->y * window_py);
    double sdx = ((1-py)/tan(angle));
    x+=sdx;
    mapx = (int) (x + player_raduis/2)/window_px;
    mapy = (int) (y - player_raduis/2)/window_py;
    if (mapy < 0 || mapy >= e->map->rows || mapx < 0 || mapx >= e->map->colomns)
        return (1);
    if (map[mapy][mapx] == '1')
        return (1);
    x+=dx;
    mapx = (int) x/window_px;
    mapy = (int) y/window_py;
    if (mapy < 0 || mapy >= e->map->rows || mapx < 0 || mapx >= e->map->colomns)
        return (1);
    if (map[mapy][mapx] == '1')
        return (1);
    return(0);
    
}

void draw_up_ray(t_elements *e, double angle)
{
    double x = e->player->px + (player_raduis / 2);
    double y = e->player->py + (player_raduis / 2);
    double dx = cos(angle) * 0.05;
    double dy = sin(angle) * 0.05;

    while (1)
    {
        int map_x = (int)(x / window_px);
        int map_y = (int)(y / window_py);

        if (map_y < 0 || map_y >= e->map->rows || map_x < 0 || map_x >= e->map->colomns)
            break;

        if (e->map->map[map_y][map_x] == '1')
            break;
        if (ray_vertical(x, y, angle) == 1)
        {
            // printf("noo\n");
            
            break;
        }
        if (ray_horizental(x, y, angle) == 1)
        {
            // printf("yess\n");
            break;
        }
        int pixel_offset = ((int)y * e->drawing->line_length) + ((int)x * (e->drawing->bits_per_pixel / 8));
        if (pixel_offset >= 0 && pixel_offset < (e->drawing->line_length * window_py * e->map->rows))
            *(unsigned int*)(e->drawing->addr + pixel_offset) = 0x00FF00; // Green ray

        x += dx;
        y -= dy;
    }
}


void render_frame(void)
{
    t_elements *element = getter();
    double  angle = element->player->angle;
    char **map = element->map->map;
    int num_rays = window_px;
    double angle_step = (VIEW) / num_rays;
     double start_angle = element->player->angle - ((VIEW) / 2);
    int i;
    int j;
    
    i = 0;
    clear_big_image(element, 0x00000000);
    while(i < element->map->rows)
    {
        j = 0;
        while (j < element->map->colomns)
        {
            if (map[i][j] == '1')
            {
                draw_wall_in_big_image(element, j * window_px, i * window_px, wall_size, wall_color);
            }
            j++;
        }
        i++;
    }
    draw_circle_in_big_image(element, element->player->px + (player_raduis / 2), element->player->py + (player_raduis / 2), player_raduis / 2, player_color);
    draw_up_ray(element, angle);
    for (int i = 0; i < num_rays; i++)
    {
        double ray_angle = start_angle + i * angle_step;
        draw_up_ray(element, ray_angle); // <-- Same function as before
    }
    // i = 0;
    // while (i < 99)
    // {
    //     draw_oblique_ray(element, alpha - (alpha / (alpha + i)));
    //     i++;
    // }
    mlx_put_image_to_window(element->drawing->mlx, element->drawing->win, element->drawing->big_image, 0, 0);
}

int    handle_keypress(int key_press, t_elements *element)
{
    int x;
    int y;
    char    **map;

    x = element->player->px;
    y = element->player->py;
    map = element->map->map;
    if (key_press == W && map[(int)((y - MOVE_SPEED ) / window_py)][(x + player_raduis)/ window_px] !='1' && map[(int)((y - MOVE_SPEED) / window_py)][x / window_px] !='1')
    {
        element->player->py -=  MOVE_SPEED;
    }else if (key_press == A &&  map[y / window_py][(int)((x - MOVE_SPEED) / window_px)] !='1' &&  map[(y + player_raduis) / window_py][(int)((x - MOVE_SPEED) / window_px)] !='1')
    {
        element->player->px -=  MOVE_SPEED;
    }else if (key_press == S && map[(int)((y + MOVE_SPEED + player_raduis) / window_py)][x / window_px] !='1' && map[(int)((y) / window_py)][(x + player_raduis) / window_px] !='1' && map[(int)((y + MOVE_SPEED + player_raduis) / window_py)][(x + player_raduis) / window_px] !='1')
    {
        element->player->py +=  MOVE_SPEED ;
    }else if (key_press == D && map[(y)/ window_py][(int)((x + MOVE_SPEED) / window_px)] !='1' && map[(y + player_raduis)/ window_py][(int)((x + MOVE_SPEED) / window_px)] !='1'  && map[(y)/ window_py][(int)((x + MOVE_SPEED + player_raduis) / window_px)] !='1'  && map[(y + player_raduis)/ window_py][(int)((x + MOVE_SPEED + player_raduis) / window_px)] !='1')
    {
        element->player->px +=  MOVE_SPEED;
    }else if (key_press == KEY_LEFT)
    {
        element->player->angle += ROTATION_SPEED;
    }else if (key_press == KEY_RIGHT)
    {
        element->player->angle -= ROTATION_SPEED;
    }
    element->player->x = (int)(element->player->px / window_px);
    element->player->y = (int)(element->player->py / window_py);
    render_frame ();
    return (0);
}


void    deb_map(void)
{
    t_elements  *element;

    element = getter();
    set_up_player();
    if (!element->player)
        ft_error_el("player not exist\n");
    printf("player her --> x=%d , y=%d\n",element->player->x, element->player->y);
    inisialise_dr();
    render_frame();
    mlx_hook(element->drawing->win, 2, 1L<<0, handle_keypress, element);
}
