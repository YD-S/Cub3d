
#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_sign(int x0, int x1)
{
	if (x0 < x1)
		return (1);
	else
		return (-1);
}

void	draw_lines(t_point point0, t_point point1, mlx_image_t *img)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;

	dx = fabsf(point1.xcoord - point0.xcoord);
	dy = -fabsf(point1.ycoord - point0.ycoord);
	err = dx + dy;
	while (1)
	{
		ft_put_pixel(img, point0.xcoord, point0.ycoord, 0x000000FF);
		if (fabsf(point0.xcoord - point1.xcoord) < 1 && fabsf(point0.ycoord - point1.ycoord) < 1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			point0.xcoord += ft_sign(point0.xcoord, point1.xcoord);
		}
		if (e2 <= dx)
		{
			err += dx;
			point0.ycoord += ft_sign(point0.ycoord, point1.ycoord);
		}
	}
}
void	free_str_array(char **array)
{
	int x;

	x = 0;
	while (array[x])
	{
		free(array[x]);
		x++;
	}
	free(array);
}

void	paint_image_black(t_mlx_data mlx_data)
{
	int		x;
	int		i;


	x = 0;
	i = 0;
	while (x < SCREEN_WIDTH)
	{
		i = 0;
		while (i < SCREEN_HEIGH)
		{
			if(i > SCREEN_HEIGH / 2)
				ft_put_pixel(mlx_data.img, x, i, get_rgba(mlx_data.map_data.F_color[0],mlx_data.map_data.F_color[1],mlx_data.map_data.F_color[2],255));
			else
				ft_put_pixel(mlx_data.img, x, i, get_rgba(mlx_data.map_data.C_color[0],mlx_data.map_data.C_color[1],mlx_data.map_data.C_color[2],255));
			i++;
		}
		x++;
	}

}

void	paint_square(int x_coord, int y_coord, t_mlx_data mlx_data,
		uint32_t color)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (x < PIXEL_SIZE)
	{
		i = 0;
		while (i < PIXEL_SIZE)
		{
			ft_put_pixel(mlx_data.img, y_coord + x, x_coord + i, color);
			i++;
		}
		x++;
	}
}

void	paint_map(t_mlx_data mlx_data)
{
	int	x_coord;
	int	y_coord;
	int	x;
	int	y;

	x = 0;
	x_coord = 0;
	y_coord = 0;
	while (x < mlx_data.map_data.heigh)
	{
		y = 0;
		y_coord = 0;
		while (y < mlx_data.map_data.width)
		{
			if (mlx_data.map_data.map[x][y].value == '1')
				paint_square(x_coord, y_coord, mlx_data, get_rgba(0, 100, 255,
							205));
			else if (mlx_data.map_data.map[x][y].value == '0'
					|| mlx_data.map_data.map[x][y].value == 'N' ||
						mlx_data.map_data.map[x][y].value == 'S' ||
						mlx_data.map_data.map[x][y].value == 'W' ||
						mlx_data.map_data.map[x][y].value == 'E')
				paint_square(x_coord, y_coord, mlx_data, get_rgba(0, 255, 155,
							205));
			y++;
			y_coord += PIXEL_SIZE;
		}
		x++;
		x_coord += PIXEL_SIZE;
	}
}

void	paint_horizontal_lines(t_mlx_data mlx_data)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (x < mlx_data.map_data.heigh - 1)
	{
		y = 1;
		while (y < mlx_data.map_data.width + 1)
		{
			if ((mlx_data.map_data.map[x][y].value == '0'
					|| mlx_data.map_data.map[x][y].value == 'N')
				&& (mlx_data.map_data.map[x + 1][y].value == '0'
					|| mlx_data.map_data.map[x + 1][y].value == 'N'
					|| mlx_data.map_data.map[x + 1][y].value == '1'))
				draw_lines(mlx_data.map_data.map[x][y].point,
							mlx_data.map_data.map[x + 1][y].point,
							mlx_data.img);
			y++;
		}
		x++;
	}
}

void	paint_vertical_lines(t_mlx_data mlx_data)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (x < mlx_data.map_data.heigh - 1)
	{
		y = 1;
		while (y < mlx_data.map_data.width + 1)
		{
			if ((mlx_data.map_data.map[x][y].value == '0'
					|| mlx_data.map_data.map[x][y].value == 'N')
				&& (mlx_data.map_data.map[x][y + 1].value == '0'
					|| mlx_data.map_data.map[x][y + 1].value == 'N'
					|| mlx_data.map_data.map[x][y + 1].value == '1'))
				draw_lines(mlx_data.map_data.map[x][y].point,
							mlx_data.map_data.map[x][y + 1].point,
							mlx_data.img);
			y++;
		}
		x++;
	}
}

t_point	get_player_position(t_mlx_data mlx_data)
{
	int		x;
	int		y;
	t_point	pos;

	x = 0;
	while (x < mlx_data.map_data.heigh)
	{
		y = 0;
		while (y < mlx_data.map_data.width)
		{
			if (mlx_data.map_data.map[x][y].value == 'N' ||
				mlx_data.map_data.map[x][y].value == 'S' ||
				mlx_data.map_data.map[x][y].value == 'E' ||
				mlx_data.map_data.map[x][y].value == 'W')
			{
				pos.xcoord = y;
				pos.ycoord = x;
				return (pos);
			}
			y++;
		}
		x++;
	}
	perror("ERROR: no player in map");
	exit(0);
}

float	grade_to_radian(float grade)
{
	float	result;

	result = grade * M_PI / 180;
	return (result);
}

float	get_player_angle(t_mlx_data mlx_data)
{
	int	x;
	int	y;

	x = 0;
	while (x < mlx_data.map_data.heigh)
	{
		y = 0;
		while (y < mlx_data.map_data.width)
		{
			if (mlx_data.map_data.map[x][y].value == 'S')
				return (0);
			else if (mlx_data.map_data.map[x][y].value == 'E')
				return (90);
			else if (mlx_data.map_data.map[x][y].value == 'N')
				return (180);
			else if (mlx_data.map_data.map[x][y].value == 'W')
				return (270);
			y++;
		}
		x++;
	}
	return (0);
}

void	put_player(t_mlx_data mlx_data)
{
	int		x;
	int		y;
	float	a;
	int		radius;

	radius = PIXEL_SIZE / 2 - 10;
	x = 0;
	while (x <= PIXEL_SIZE)
	{
		y = 0;
		while (y <= PIXEL_SIZE)
		{
			if (pow(((mlx_data.player.position.xcoord - PIXEL_SIZE / 2 + x)
						- (mlx_data.player.position.xcoord)), 2)
				+ pow(((mlx_data.player.position.ycoord - PIXEL_SIZE / 2 + y)
						- (mlx_data.player.position.ycoord)), 2) <= pow(radius,
																																																									2))
			{
				ft_put_pixel(mlx_data.img, mlx_data.player.position.xcoord
						- PIXEL_SIZE / 2 + x, mlx_data.player.position.ycoord
						- PIXEL_SIZE / 2 + y, get_rgba(255, 0, 0, 255));
			}
			y++;
		}
		x++;
	}
	a = 0;
	while (a <= M_PI * 2)
	{
		x = cos(a) * radius + mlx_data.player.position.xcoord;
		y = sin(a) * radius + mlx_data.player.position.ycoord;
		ft_put_pixel(mlx_data.img, x, y, get_rgba(0, 0, 0, 255));
		a += 0.01;
	}
}

t_projection_data	init_proj_data()
{
	t_projection_data	proj_data;

	proj_data.n_rays = 30 / RAY_DIV;
	proj_data.ray_array = ft_calloc(proj_data.n_rays + 1, sizeof(t_ray));
	return (proj_data);
}

void ft_get_texture(t_mlx_data *mlx_data)
{
	mlx_data->map_data.texture.NO = mlx_load_png(mlx_data->map_data.NO);
	mlx_data->map_data.texture.EA = mlx_load_png(mlx_data->map_data.EA);
	mlx_data->map_data.texture.SO = mlx_load_png(mlx_data->map_data.SO);
	mlx_data->map_data.texture.WE = mlx_load_png(mlx_data->map_data.WE);
}

void	open_map(t_mlx_data mlx_data)
{
	mlx_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGH, "cub3d", false);
	mlx_set_cursor_mode(mlx_data.mlx, MLX_MOUSE_HIDDEN);
	mlx_data.img = mlx_new_image(mlx_data.mlx, 1920, 1080);
	mlx_image_to_window(mlx_data.mlx, mlx_data.img, 0, 0);
	ft_get_texture(&mlx_data);
	paint_image_black(mlx_data);
	paint_map(mlx_data);
	paint_horizontal_lines(mlx_data);
	paint_vertical_lines(mlx_data);
	mlx_data.player = init_player(mlx_data);
	put_player(mlx_data);
	mlx_data.proj_data = init_proj_data();
	mlx_data = put_ray(mlx_data);
	projection(mlx_data);
	mlx_key_hook(mlx_data.mlx, &hook, (void *)&mlx_data);
	mlx_cursor_hook(mlx_data.mlx, &cursor_hook, (void *)&mlx_data);
	mlx_loop_hook(mlx_data.mlx, (void *)&repaint_map, (void *)&mlx_data);
	mlx_loop(mlx_data.mlx);
}
