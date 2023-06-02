
#include "cub3d.h"

t_mlx_data	init_mlx_data(char *map_name)
{
	t_mlx_data	mlx_data;

	mlx_data.map_data = parse_map(map_name);
	return (mlx_data);
}

t_player	init_player(t_mlx_data mlx_data)
{
	t_player player;
	t_point pos;

	player.position.xcoord = get_player_position(mlx_data).xcoord * PIXEL_SIZE
		+ PIXEL_SIZE / 2;
	player.position.ycoord = get_player_position(mlx_data).ycoord * PIXEL_SIZE
		+ PIXEL_SIZE / 2;
	player.angle = get_player_angle(mlx_data);
	return (player);
}