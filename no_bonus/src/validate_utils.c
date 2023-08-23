#include "cub3d.h"

void	free_t_map(t_map **map)
{
	int	x;

	x = 0;
	while (map[x])
	{
		free(map[x]);
		x++;
	}
	free(map);
	exit_error("Error\nMap must have one player\n");
}
