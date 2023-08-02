#include "cub3d.h"

int master_validate(t_mlx_data mlx_data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j != mlx_data.map_data.width)
	{
		if (check_first_line(mlx_data.map_data.map, i, j) == 0)
			return (0);
		j++;
	}
	i = 0;
	j = 0;
	while (i != mlx_data.map_data.heigh)
	{
		if (check_last_line(mlx_data.map_data.map, i, j) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		check_first_line(t_map **map, int i, int j)
{
	if (map[i][j].value == '1')
		return (1);
	if (map[i][j].value == ' ')
	{
		if (check_first_line(map, i, j - 1) == 1)
			return (1);
		if (check_first_line(map, i - 1, j) == 1)
			return (1);
		if (check_first_line(map, i, j + 1) == 1)
			return (1);
		if (check_first_line(map, i + 1, j) == 1)
			return (1);
	}
	return (0);
}

int		check_last_line(t_map **map, int i, int j)
{
	if (map[i][j].value == '1')
		return (1);
	if (map[i][j].value == ' ')
	{
		if (check_last_line(map, i, j - 1) == 1)
			return (1);
		if (check_last_line(map, i - 1, j) == 1)
			return (1);
		if (check_last_line(map, i, j + 1) == 1)
			return (1);
		if (check_last_line(map, i + 1, j) == 1)
			return (1);
	}
	return (0);
}
