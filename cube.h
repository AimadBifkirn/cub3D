#ifndef CUBE_H
#define CUBE_H

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
#include <sys/wait.h>
#include <math.h>

// #define window_px 16
// #define window_py 16
#define wall_color 0x00FF0000
#define player_color 0x00FFFF00
#define player_raduis 7
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05
#define PI 3.14285714286
#define alpha (PI/2 - PI/8)
#define square_size 10
#define fov PI / 3 //a FOV of 60° in radian
#define screen_width 800
#define screen_height 600


// aimad : it is for drawing mini_map, need it cause of norminette :|
typedef struct s_mini_map
{
    int	start_y;
	int	start_x;
	int	end_y;
	int	end_x;
}   t_m_map;



typedef struct s_color
{
    int a;
    int b;
    int c;
}t_color;


typedef struct s_map
{
    int rows;
    int colomns;
    char **map;
}t_map;

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
	// int		direction_x;
	// int		direction_y;
    // double  plane_x;
    // double  plane_y;
    double  angle;
}	t_player;

typedef struct s_draw
{
    double  start_angle;
    double  step_angle;
    double  ray_angle;
    double  ray_dir_x;
    double  ray_dir_y;
    double  delta_dist_x; // bach tchof bchehal ghatzid bach tfot tail
    double  delta_dist_y;
    int		step_x;
    int		step_y;
    double  side_dist_x;
    double  side_dist_y;
	int		map_x;
	int		map_y;
    int     side;
    int		wall_height;
}t_draw;


typedef struct s_elements
{
    // t_draw  *drawing;
    char    *no;
    char    *so;
    char    *ea;
    char    *we;
    void    *mlx;
    void    *wind;
    void    *img;
    char    *addr;
    int     bits_per_px;
    int     line_len;
    int     endian;
    t_texture   textures[4];
    t_color *f;
    t_color *c;
    t_map   *map;
    t_player    *player;
}   t_elements;


void        parcing_mn(int ac, char **argv);
// void        render_frame(void);
// void        inisialise_dr(void);
// void        clear_big_image(t_elements *element, int bg_color);
void        map(char **argv);
int         copy_map(char *line, int fd);
int         upload_map(char **argv);
void        strlen_exit(void);
void        ft_error(const char *str);
void        ft_error_el(const char *str);
int         ff_strlen(const char *str);
t_elements  *getter(void);
void        ft_bzero(void *s, size_t n);
int         extruct_map(char *line, int fd);
int         start_map(char *line, int fd);
char        *ft_strnext( char *haystack, const char *needle);
int         extruct_elements(char *line);
int         extruct_them(char *line);
void        cheack_map(void);
void        print_map(t_elements *element);
// void        deb_map(void);


//player
// void        set_up_player(void);
// void        deb_map(void);
// void        inisialise_dr(void);
// void        set_up_player(void);
// void        render_frame(void);
// get_next_line

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif


char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*reset_res(char *reserve);
char	*read_mine(int fd);
char	*get_line(char *reserve);
void	ft_memcpy(char *s1, char *s2, size_t i);

// libft
char	**ft_split(char const *s, char c);
int     ft_atoi(const char *str);
// aimad's part
void	ray_casting(t_elements *elem);
void	render(t_elements *elem);
int     event_handeler(int code, t_elements *elem);
void    put_pixel_to_image(t_elements *elem, int x, int y, int color);
int     is_free(double x, double y, char **map);
void	draw_mini_map(t_elements *elem);
void	initalize_draw_elems(t_draw *darw, int i, t_elements *elem);

#endif
