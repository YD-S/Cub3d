#include "cub3d.h"

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
