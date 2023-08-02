#include "cub3d.h"

int flood_fill(t_map_data map, int x, int y)
{
	if (map.map[x][y].value == '1' || map.map[x][y].value == 'Q')
		return (1);
	if(x < 0 || x > map.heigh + 1 || y < 0 || y > map.width + 1 || map.map[x][y].value == ' ')
		exit(0);
	if (map.map[x][y].value == '0')
	{
		map.map[x][y].value = 'Q';
		if (flood_fill(map, x + 1, y) == 1)
			return (1);
		if (flood_fill(map, x - 1, y) == 1)
			return (1);
		if (flood_fill(map, x, y + 1) == 1)
			return (1);
		if (flood_fill(map, x, y - 1) == 1)
			return (1);
	}
	return (0);
}

int master_validate(t_mlx_data mlx_data)
{
	flood_fill(mlx_data.map_data, mlx_data.player.position.xcoord / PIXEL_SIZE, mlx_data.player.position.ycoord / PIXEL_SIZE);
	return (1);
}
