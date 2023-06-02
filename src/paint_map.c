
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
	while (1 == 1)
	{
		mlx_put_pixel(img, point0.xcoord, point0.ycoord, 0x000000FF);
		if (point0.xcoord == point1.xcoord && point0.ycoord == point1.ycoord)
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

void	paint_image_black(t_mlx_data mlx_data)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (x < 1920)
	{
		i = 0;
		while (i < 1080)
		{
			mlx_put_pixel(mlx_data.img, x, i, 0x000000FF);
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
			mlx_put_pixel(mlx_data.img, y_coord + x, x_coord + i, color);
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
				return (grade_to_radian(0));
			else if (mlx_data.map_data.map[x][y].value == 'E')
				return (grade_to_radian(90));
			else if (mlx_data.map_data.map[x][y].value == 'N')
				return (grade_to_radian(180));
			else if (mlx_data.map_data.map[x][y].value == 'W')
				return (grade_to_radian(270));
			y++;
		}
		x++;
	}
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
				mlx_put_pixel(mlx_data.img, mlx_data.player.position.xcoord
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
		mlx_put_pixel(mlx_data.img, x, y, get_rgba(0, 0, 0, 255));
		a += 0.01;
	}
}

// t_point	point_to_angle(t_point point)
// {
// 	t_point angle_point;

// 	angle_point.xcoord =
// }

void	put_ray(t_mlx_data mlx_data)
{
	t_point	point1;

	point1.xcoord = roundf(mlx_data.player.position.xcoord + 50
			* sin(mlx_data.player.angle));
	point1.ycoord = roundf(mlx_data.player.position.ycoord + 50
			* cos(mlx_data.player.angle));
	draw_lines(mlx_data.player.position, point1, mlx_data.img);
}

void	open_map(t_mlx_data mlx_data)
{
	mlx_data.mlx = mlx_init(1920, 1080, "cub3d", false);
	mlx_data.img = mlx_new_image(mlx_data.mlx, 1920, 1080);
	paint_image_black(mlx_data);
	mlx_image_to_window(mlx_data.mlx, mlx_data.img, 0, 0);
	paint_map(mlx_data);
	paint_horizontal_lines(mlx_data);
	paint_vertical_lines(mlx_data);
	mlx_data.player = init_player(mlx_data);
	put_player(mlx_data);
	put_ray(mlx_data);
	mlx_key_hook(mlx_data.mlx, &hook, (void *)&mlx_data);
	mlx_loop(mlx_data.mlx);
}
