
#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "math.h"

# define PIXEL_SIZE 40
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGH 1080
# define RAY_DIV 0.02

typedef struct s_point
{
	long int		xcoord;
	long int		ycoord;
}				t_point;

typedef struct s_map
{
	char		value;
	t_point		point;
}				t_map;

typedef struct s_map_data
{
	t_map		**map;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*F;
	char		*C;
	int			heigh;
	int			width;
}				t_map_data;

typedef struct s_player
{
	t_point		position;
	int			angle;
}				t_player;

typedef struct s_ray
{
	t_point	end_point;
	int		distance;
	float	angle;
}	t_ray;

typedef struct s_projection_data
{
	int		n_rays;
	t_ray	*ray_array;

}	t_projection_data;

typedef struct s_mlx_data
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	t_map_data			map_data;
	t_player			player;
	t_projection_data	proj_data;

}				t_mlx_data;

t_map_data		parse_map(char *map);
void			open_map(t_mlx_data mlx_data);
t_mlx_data		init_mlx_data(char *map_name);
t_player		init_player(t_mlx_data mlx_data);
void			hook(struct mlx_key_data keydata, void *param);
void			put_player(t_mlx_data mlx_data);
void			paint_image_black(t_mlx_data mlx_data);
void			paint_map(t_mlx_data mlx_data);
void			paint_horizontal_lines(t_mlx_data mlx_data);
void			paint_vertical_lines(t_mlx_data mlx_data);
t_mlx_data			put_ray(t_mlx_data mlx_data);
float			grade_to_radian(float grade);
t_point			get_player_position(t_mlx_data mlx_data);
float			get_player_angle(t_mlx_data mlx_data);
void			draw_lines(t_point point0, t_point point1, mlx_image_t *img);
int	get_rgba(int r, int g, int b, int a);
int master_validate(t_mlx_data mlx_data);
int		check_first_line(t_map **map, int i, int j);
int		check_last_line(t_map **map, int i, int j);
void	projection(t_mlx_data mlx_data);
void	paint_square_td(t_mlx_data mlx_data, int distance, int x_start);
#endif // CUB3D_H
