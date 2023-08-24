/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:53:59 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 21:50:00 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "math.h"
# include "signal.h"

# define PIXEL_SIZE (16)
# define SCREEN_WIDTH 1270.
# define SCREEN_HEIGH 720.
# define RAY_DIV (30 / SCREEN_WIDTH)
# define WALL_HEIGHT_SCALE (25)

typedef struct s_point
{
	float				xcoord;
	float				ycoord;
	int					type;
}						t_point;

typedef struct s_map
{
	char				value;
	t_point				point;
}						t_map;
typedef struct s_txtures
{
	mlx_texture_t		*no;
	mlx_texture_t		*so;
	mlx_texture_t		*ea;
	mlx_texture_t		*we;
}						t_textures;

typedef struct s_map_data
{
	t_map				**map;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*f;
	char				*c;
	int					*f_color;
	int					*c_color;
	int					heigh;
	int					width;
	t_textures			texture;
}						t_map_data;

typedef struct s_player
{
	t_point				position;
	int					angle;
}						t_player;

typedef struct s_ray
{
	t_point				end_point;
	float				distance;
	float				angle;
	int					ray_heigh;
}						t_ray;

typedef struct s_projection_data
{
	int					n_rays;
	t_ray				*ray_array;

}						t_projection_data;

typedef struct s_ints
{
	int					dx;
	int					dy;
	int					err;
	int					e2;

}						t_ints;

typedef struct t_counts
{
	int					i;
	int					fd;
	int					x;
	int					j;

}						t_counts;

typedef struct s_mlx_data
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	t_map_data			map_data;
	t_player			player;
	t_projection_data	proj_data;

}						t_mlx_data;

typedef struct s_norm_vars
{
	float				yn;
	float				xn;
	float				x;
	float				y;
	t_point				p1;
}						t_norm_vars;

void					free_map(t_map_data map_data);
void					print_map(t_map_data map_data);
int						verify_path(char *str);
t_mlx_data				init_mlx_data(char *map_name);
t_player				init_player(t_mlx_data mlx_data);
void					*repaint_map(void *param);
void					call_movement_hooks(t_mlx_data *mlx_data,
							struct mlx_key_data keydata);
int						collision(t_mlx_data *data, float x, float y);
float					get_xcord(t_mlx_data mlx_data, t_point vel);
float					get_ycord(t_mlx_data mlx_data, t_point vel);
void					hook(struct mlx_key_data keydata, void *param);
void					cursor_hook(double xpos, double ypos, void *param);
char					*parse_no(char *line);
char					*parse_we(char *line);
char					*parse_so(char *line);
char					*parse_ea(char *line);
char					*parse_f(char *line);
char					*parse_c(char *line);
t_map_data				parse_line(char *line, t_map_data map_data);
t_map_data				map_data_init(void);
t_map_data				read_map_utils(char *map);
int						get_map_heigh(char *map);
int						get_map_width(char *map);
t_map					**get_map_malloc(t_map_data map_data);
t_map					**fill_map_spaces(t_map **map, t_map_data map_data);
t_map					**fill_map_values(t_map **map, char *map_name);
t_map					**get_map(char *map_name, t_map_data map_data);
int						*init_f_color(t_map_data map_data);
int						*init_c_color(t_map_data map_data);
t_map_data				parse_map(char *map);
int						get_rgba(int r, int g, int b, int a);
int						ft_sign(int x0, int x1);
void					draw_lines(t_point point0, t_point point1,
							mlx_image_t *img);
void					free_str_array(char **array);
void					paint_image_black(t_mlx_data mlx_data);
void					paint_square(int x_coord, int y_coord,
							t_mlx_data mlx_data, uint32_t color);
void					paint_map(t_mlx_data mlx_data);
void					paint_horizontal_lines(t_mlx_data mlx_data);
void					paint_vertical_lines(t_mlx_data mlx_data);
t_point					get_player_position(t_mlx_data mlx_data);
float					grade_to_radian(float grade);
float					get_player_angle(t_mlx_data mlx_data);
void					put_player(t_mlx_data mlx_data);
t_projection_data		init_proj_data(void);
void					ft_get_texture(t_mlx_data *mlx_data);
void					open_map(t_mlx_data mlx_data);
void					ft_print_big_dot(mlx_image_t *img, float xcoord,
							float ycoord, uint32_t color);
int						radian_to_angle(float radian);
t_point					check_horizontal_steps(t_mlx_data mlx_data,
							float angle);
t_point					check_vertical_steps(t_mlx_data mlx_data, float angle);
int						check_bug_hor(t_mlx_data mlx_data, t_point point);
int						check_bug_ver(t_mlx_data mlx_data, t_point point);
t_point					check_distance(t_mlx_data mlx_data, float angle);
t_mlx_data				put_ray(t_mlx_data mlx_data);
char					ft_texture(t_mlx_data *mlx_data, int x, int y);
int						getxtex(char tex, int x, t_mlx_data mlx_data);
float					getstep(int height, t_mlx_data mlx_data, char tex);
uint32_t				reversecolor(unsigned int coloraux);
uint32_t				gettexcolor(char tex, int x, int y,
							t_mlx_data mlx_data);
void					paint_square_td(t_mlx_data mlx_data, int height,
							int x_start, int color);
void					ft_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
							uint32_t color);
void					projection(t_mlx_data mlx_data);
void					master_validate(t_mlx_data mlx_data);
int						check_first_line(t_map **map, int i, int j);
int						check_last_line(t_map **map, int i, int j);
void					validate_map(t_mlx_data mlx_data);
t_map_data				do_no(char *line, t_map_data map_data);
t_map_data				do_so(char *line, t_map_data map_data);
t_map_data				do_ea(char *line, t_map_data map_data);
t_map_data				do_we(char *line, t_map_data map_data);
int						condition1(t_mlx_data mlx_data, int x, int y);
void					free_t_map(t_map **map);
void					exit_error(char *error_message);
void					init_all(int *x, int *i, char **line, int fd);
int						condition2(t_mlx_data mlx_data, int angle);
int						condition3(t_mlx_data mlx_data, int x, int y,
							int angle);
int						condition4(t_mlx_data mlx_data, int x, int y,
							int angle);
int						condition5(t_mlx_data mlx_data, int x, int y);
t_norm_vars				init_norm_vars(void);
int						radian_to_angle(float radian);
t_point					horiz_1st_loop(t_mlx_data mlx_data, float x,
							float y, float angle);
t_point					horiz_2nd_loop(t_mlx_data mlx_data, float x,
							float y, float angle);
t_point					check_horizontal_steps(t_mlx_data mlx_data,
							float angle);
int						check_bug_hor(t_mlx_data mlx_data, t_point point);

t_point					ver_1st_loop(t_mlx_data mlx_data, float x, float y,
							float angle);
t_point					ver_2nd_loop(t_mlx_data mlx_data, float x, float y,
							float angle);
t_point					check_vertical_steps(t_mlx_data mlx_data, float angle);
int						check_bug_ver(t_mlx_data mlx_data, t_point point);
void					ft_put_pixel(mlx_image_t *img, uint32_t x,
							uint32_t y, uint32_t color);
uint32_t				reversecolor(unsigned int coloraux);
uint32_t				gettexcolor(char tex, int x, int y,
							t_mlx_data mlx_data);
void					paint_square_td(t_mlx_data mlx_data, int height,
							int x_start, int color);
void					projection(t_mlx_data mlx_data);
void					do_cpy(t_map **map, t_map **cpy_map, int x, int y);

#endif // CUB3D_H
