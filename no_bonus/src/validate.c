#include "cub3d.h"

t_map **cpy_map(t_map **map)
{
	int		x;
	int		y;
	t_map	**cpy_map;

	x = 0;
	while (map[x])
		x++;
	cpy_map = malloc(sizeof(t_map *) * (x + 1));
	if (!cpy_map)
		return (NULL);
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y].value)
			y++;
		cpy_map[x] = malloc(sizeof(t_map) * (y + 1));
		if (!cpy_map[x])
			return (NULL);
		y = 0;
		while (map[x][y].value)
		{
			cpy_map[x][y].value = map[x][y].value;
			cpy_map[x][y].point.xcoord = map[x][y].point.xcoord;
			cpy_map[x][y].point.ycoord = map[x][y].point.ycoord;
			cpy_map[x][y].point.type = map[x][y].point.type;
			y++;
		}
		cpy_map[x][y].value = '\0';
		x++;
	}
	cpy_map[x] = NULL;
	return (cpy_map);
}

void exit_error(char *error_message)
{
	printf("%s", error_message);
	exit(0);
}

int check_player(t_map **map)
{
	int x = 0;
	int y = 0;
	int player = 0;

	while (map[y])
	{
		while (map[y][x].value)
		{
			if (map[y][x].value == 'N' || map[y][x].value == 'S' || map[y][x].value == 'E' || map[y][x].value == 'W')
				player++;
			x++;
		}
		x = 0;
		y++;
	}
	if (player != 1)
	{
		x = 0;
		while (map[x])
		{
			free(map[x]);
			x++;
		}
		free(map);
		exit_error("Error\nMap must have one player\n");
		return 0;
	}
	return 1;
}

int flood_fill(t_map **map, int x, int y, t_mlx_data *mlx_data)
{
	if(x < 0 || x > mlx_data->map_data.width || y < 0 || y > mlx_data->map_data.heigh || map[y][x].value == ' ')
		exit_error("Error\nMap must be surrounded by 1 or ' '\n");
	if (map[y][x].value == '1' || map[y][x].value == 'Q')
		return (1);
	if (map[y][x].value == '0' || map[y][x].value == 'N' || map[y][x].value == 'S' || map[y][x].value == 'E' || map[y][x].value == 'W')
	{
		map[y][x].value = 'Q';
		flood_fill(map, x + 1, y, mlx_data);
		flood_fill(map, x - 1, y, mlx_data);
		flood_fill(map, x, y + 1, mlx_data);
		flood_fill(map, x, y - 1, mlx_data);
	}
	return (0);
}

void master_validate(t_mlx_data mlx_data)
{
	t_map **map;
	int j = 0;
	map = cpy_map(mlx_data.map_data.map);
	int x = get_player_position(mlx_data).xcoord * PIXEL_SIZE
		+ PIXEL_SIZE / 2;
	int y = get_player_position(mlx_data).ycoord * PIXEL_SIZE
		+ PIXEL_SIZE / 2;
	flood_fill(map, x / PIXEL_SIZE, y / PIXEL_SIZE, &mlx_data);
	check_player(map);
	while (map[j])
	{
		free(map[j]);
		j++;
	}
	free(map);
}
