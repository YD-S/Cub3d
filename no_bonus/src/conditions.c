#include "cub3d.h"

int	condition1(t_mlx_data mlx_data, int x, int y)
{
	return (mlx_data.map_data.map[x][y].value == 'N'
			|| mlx_data.map_data.map[x][y].value == 'S'
			|| mlx_data.map_data.map[x][y].value == 'E'
			|| mlx_data.map_data.map[x][y].value == 'W');
}

int	condition2(t_mlx_data mlx_data, int angle)
{
	return (abs((int)(mlx_data.player.angle + angle) % 360) <= 270
		&& abs(((int)(mlx_data.player.angle + angle) % 360) >= 90));
}

int	condition3(t_mlx_data mlx_data, int x, int y, int angle)
{
	return ((mlx_data.player.angle % 360) + angle < 90
		&& mlx_data.map_data.map[(int)((y) / PIXEL_SIZE)]
		[(int)((x) / PIXEL_SIZE)].value == '1');
}

int	condition4(t_mlx_data mlx_data, int x, int y, int angle)
{
	return ((mlx_data.player.angle % 360) + angle >= 90
		&& mlx_data.map_data.map[(int)((y) / PIXEL_SIZE)]
		[(int)((x) / PIXEL_SIZE)].value == '1');
}

int	condition5(t_mlx_data mlx_data, int x, int y)
{
	return (x < 0 || y < 0 || x > (mlx_data.map_data.width - 1) * PIXEL_SIZE
		|| y > (mlx_data.map_data.heigh - 1) * PIXEL_SIZE
		|| ((y / PIXEL_SIZE) - 1) > mlx_data.map_data.heigh
		|| (x / PIXEL_SIZE) > mlx_data.map_data.width);
}
