/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:37:33 by abifkirn          #+#    #+#             */
/*   Updated: 2025/08/21 15:49:47 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <sys/wait.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// # define wall_color 0x00FF0000
// # define player_color 0x00FFFF00
# define MAX_DRAW_DISTANCE 20.0
# define MOVE_SPEED 0.01
# define ROT_SPEED 0.01
# define PI 3.14285714286
// # define alpha (PI/2 - PI/8)
// # define square_size 10
# define FOV PI / 3 //a FOV of 60° in radian
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 720
# define MINIMAP_TILE_SIZE 8
# define MINIMAP_RADIUS 10
# define MINIMAP_SIZE (2 * MINIMAP_RADIUS * MINIMAP_TILE_SIZE)

typedef struct s_mini_map
{
	int	start_y;
	int	start_x;
	int	end_y;
	int	end_x;
}	t_m_map;

typedef struct s_color
{
	int	a;
	int	b;
	int	c;
}	t_color;

typedef struct s_map
{
	int		rows;
	int		colomns;
	char	**map;
}	t_map;

typedef struct s_texture
{
	void	*img_ptr;
	int		*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_draw
{
	int		door;
	int		enemy;
	double	start_angle;
	double	step_angle;
	double	ray_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x; // bach tchof bchehal ghatzid bach tfot tail
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		side;
	int		wall_height;
	double	dist_to_wall;
}	t_draw;

typedef struct s_enemy
{
	int			x;
	int			y;
	t_texture	textures[10];
	float		xf;
	float		yf;
}	t_enemy;

typedef struct s_collecter
{
	void				*single1;
	struct s_collecter	*next;
}	t_collecter;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_elements
{
	char		*no;
	t_keys		keys;
	char		*so;
	char		*ea;
	char		*we;
	void		*mlx;
	void		*wind;
	void		*img;
	char		*addr;
	int			bits_per_px;
	int			line_len;
	int			endian;
	int			shooting;
	t_texture	textures[6];
	t_color		*f;
	t_color		*c;
	t_map		*map;
	t_player	*player;
	t_enemy		*enemy;
	int			j;
}	t_elements;

void		parcing_mn(int ac, char **argv);
void		map(char **argv);
int			copy_map(char *line, int fd);
int			upload_map(char **argv);
void		strlen_exit(void);
void		ft_error(const char *str);
void		ft_error_el(const char *str);
int			ff_strlen(const char *str);
t_elements	*getter(void);
void		ft_bzero(void *s, size_t n);
int			extruct_map(char *line, int fd);
int			start_map(char *line, int fd);
char		*ft_strnext( char *haystack, const char *needle);
int			extruct_elements(char *line);
int			extruct_them(char *line);
void		cheack_map(void);
void		valid_character(t_elements *elem);
void		draw_pistol(t_elements *elem, t_texture *tex, int size);
char		*get_next_line(int fd);
t_draw		*getter_draw(void);
size_t		ft_strlen(char *s);
char		*ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
char		*reset_res(char *reserve);
char		*read_mine(int fd);
char		*get_line(char *reserve);
void		ft_memcpy(char *s1, char *s2, size_t i);
// libft
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *str);
// aimad's part
void		ray_casting(t_elements *elem);
void		render(t_elements *elem);
int			event_handeler(int code, t_elements *elem);
void		put_pixel_to_image(t_elements *elem, int x, int y, int color);
int			is_free(double x, double y, char **map);
void		draw_mini_map(t_elements *elem);
char		*extruct_link(char *str);
void		initalize_draw_elems(t_draw *darw, int i, t_elements *elem);
int			mouse_move_handler(int x, int y, t_elements *elem);
int			check_button(int code, int x, int y, void *elem);
int			key_release(int code, t_elements *elem);
void		rotate_right(t_elements *elem);
void		rotate_left(t_elements *elem);
void		move_right(t_elements *elem);
void		move_left(t_elements *elem);
void		move_backward(t_elements *elem);
void		move_forward(t_elements *elem);
char		*get_c(t_elements *element, char *line, char *str);
char		*get_f(t_elements *element, char *line, char *str);
char		*get_no(t_elements *element, char *line, char *str);
char		*get_so(t_elements *element, char *line, char *str);
char		*get_we(t_elements *element, char *line, char *str);
char		*get_ea(t_elements *element, char *line, char *str);
void		ft_esc(const char *str);
int			close_window(void *param);
char		*extruct_tex_col(char *line, int fd);
int			extruct_mmp(char *line, int fd, int i, int ismap);
int			help_copy(t_elements *element, char *line, int *j);
void		check_space(t_elements *element, int i, int j);
t_collecter	**getter_garbage(void);
void		add_back(t_collecter *new_node);
void		*ft_malloc(size_t size);
void		ft_free_all(void);
void		ft_free(void *pointer);
t_collecter	**getter_garbage(void);
t_elements	*getter(void);
void		put_enemy(t_elements *element);
void		put_doors(t_elements *element);
void		close_doors(t_elements *elem);
void		initalize_draw_elems(t_draw *draw, int i, t_elements *elem);
void		drawing(t_elements *elem, double dist, int i, t_draw draw);
long		get_texture_pixel(t_texture *tex, int x, int y);
long		get_color(t_elements *elem, t_draw draw, int y);
void		load_textures(t_elements *elem);
t_texture	*get_texture(t_elements *elem, t_draw *draw);
void		get_player_direction(t_elements *elem);
void		draw_map(t_elements *elem);
void		draw_background(t_elements *elem);
t_m_map		init_elements(t_elements *elem);
void		put_pixels(t_elements *elem, int x, int y);
void		error_textures(char *str, int i);
void		valid_char(char *line, int *val1, int *val2);
void		limiters_valmap(char *line, int fd, t_elements *element);
void		put_it(t_elements *elem, t_texture *tex, int size, int *data);
int			color_val(t_texture *tex, int *first_pixel_y, int *last_pixel_y);
void		destroy_win_des(t_elements *element);

#endif
