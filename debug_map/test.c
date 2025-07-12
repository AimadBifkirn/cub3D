// Update your t_draw struct to include buffer
typedef struct s_draw
{
    void    *mlx;
    void    *win;
    void    *wall_img;
    void    *player_img;
    void    *buffer_img;        // Add this - big window-sized buffer
    char    *buffer_addr;       // Add this - buffer memory access
    int     bits_per_pixel;     // Add this
    int     line_length;        // Add this
    int     endian;             // Add this
    int     win_width;          // Add this
    int     win_height;         // Add this
}t_draw;

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
            if (element->map->map[i][j] == 'N' || element->map->map[i][j] == 'S' || element->map->map[i][j] == 'O' || element->map->map[i][j] == 'e')
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
                element->map->map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
}

// Function to put pixel directly in the big buffer
void put_pixel_to_buffer(t_elements *element, int x, int y, int color)
{
    int pixel_offset;
    
    // Check bounds
    if (x < 0 || x >= element->drawing->win_width || 
        y < 0 || y >= element->drawing->win_height)
        return;
    
    // Calculate pixel position in buffer
    pixel_offset = (y * element->drawing->line_length) + (x * (element->drawing->bits_per_pixel / 8));
    
    // Set pixel color in buffer
    *(unsigned int*)(element->drawing->buffer_addr + pixel_offset) = color;
}

// Draw rectangle directly to buffer (no small images)
void draw_rectangle_to_buffer(t_elements *element, int x, int y, int width, int height, int color)
{
    int i, j;
    
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            put_pixel_to_buffer(element, x + j, y + i, color);
        }
    }
}

// Draw circle directly to buffer (no small images)
void draw_circle_to_buffer(t_elements *element, int center_x, int center_y, int radius, int color)
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
                put_pixel_to_buffer(element, x, y, color);
        }
    }
}

// Clear the entire buffer
void clear_buffer(t_elements *element, int bg_color)
{
    int total_pixels = element->drawing->win_width * element->drawing->win_height;
    int i;
    
    for (i = 0; i < total_pixels; i++)
    {
        ((unsigned int*)element->drawing->buffer_addr)[i] = bg_color;
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
    
    // Calculate window dimensions
    element->drawing->win_width = element->map->colomns * 16;
    element->drawing->win_height = element->map->rows * 16;
    
    // Create ONE big buffer image (size of entire window)
    element->drawing->buffer_img = mlx_new_image(element->drawing->mlx, 
                                                element->drawing->win_width, 
                                                element->drawing->win_height);
    if (!element->drawing->buffer_img)
        ft_error_el("buffer creation failed\n");
    
    // Get buffer memory access
    element->drawing->buffer_addr = mlx_get_data_addr(
        element->drawing->buffer_img,
        &element->drawing->bits_per_pixel,
        &element->drawing->line_length,
        &element->drawing->endian
    );
    
    // You can still keep these for compatibility, but we won't use them for rendering
    element->drawing->player_img = create_circle_image(element, player_raduis, player_color);
    element->drawing->wall_img = create_colored_image(element, window_py, window_px, wall_color);
    
    element->drawing->win = mlx_new_window(element->drawing->mlx, 
                                          element->drawing->win_width, 
                                          element->drawing->win_height, "Cub3D");
}

// NEW OPTIMIZED RENDER - draws everything to buffer, then displays once
void render_frame(void)
{
    t_elements *element = getter();
    char **map = element->map->map;
    int i, j;
    
    // 1. Clear the entire buffer (black background)
    clear_buffer(element, 0x00000000);
    
    // 2. Draw all walls directly to buffer (no individual images)
    i = 0;
    while(i < element->map->rows)
    {
        j = 0;
        while (j < element->map->colomns)
        {
            if (map[i][j] == '1')
            {
                // Draw wall rectangle directly to buffer
                draw_rectangle_to_buffer(element, j * 16, i * 16, 16, 16, wall_color);
            }
            j++;
        }
        i++;
    }
    
    // 3. Draw player circle directly to buffer
    draw_circle_to_buffer(element, 
                         element->player->px, 
                         element->player->py, 
                         player_raduis, 
                         player_color);
    
    // 4. Display the ENTIRE buffer to window in ONE operation (smooth!)
    mlx_put_image_to_window(element->drawing->mlx, element->drawing->win, 
                           element->drawing->buffer_img, 0, 0);
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
}

// Clean up function
void cleanup_rendering(void)
{
    t_elements *element = getter();
    
    if (element->drawing->buffer_img)
        mlx_destroy_image(element->drawing->mlx, element->drawing->buffer_img);
    if (element->drawing->wall_img)
        mlx_destroy_image(element->drawing->mlx, element->drawing->wall_img);
    if (element->drawing->player_img)
        mlx_destroy_image(element->drawing->mlx, element->drawing->player_img);
}
